#include <iostream>
#include <conio.h>
#include <windows.h>
#include <fstream>
#include "utils.h"
#include "maze.h"
using namespace std;

const int scrW = 150;

void moveCursorTo(short x, short y) {
	COORD cursor = {y, x};
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), cursor);
}

void setColor(int x) {
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), x);
}

void showCursor(bool showFlag) {
    HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_CURSOR_INFO cursorInfo;
    GetConsoleCursorInfo(handle, &cursorInfo);
    cursorInfo.bVisible = showFlag;
    SetConsoleCursorInfo(handle, &cursorInfo);
}

void startGame(int Rows, int Cols, int difficulty, int timeLimit, int chosenTheme) {
	system("cls");
	Maze maze(Rows, Cols, timeLimit, difficulty, chosenTheme);

    maze.generate();
	maze.startGame();
}

void printBanner() {
    ifstream file("./text/banner.txt");
	if (file.is_open()) {
		string s;
		for (int i = 0; getline(file, s); ++i) {

            if (i == 0 || i == 1 || i == 7 || i == 8) setColor(10);
            else if (i == 2 || i == 9) setColor(11);
            else if (i == 3 || i == 10) setColor(14);
            else if (i == 4 || i == 11) setColor(12);

			moveCursorTo(i + 2, (scrW - s.size()) / 2);
			cout << s;
		}
		file.close();

	} else {
        exit(1);
    }
}

void printTxt(const char * s) {
    ifstream file(s);
    if (file.is_open()) {
        string s;
        setColor(10);
        for (int i = 0; getline(file, s); ++i) {
            moveCursorTo(i + 18, (scrW + 1 - s.size()) / 2);
            cout << s;
        }
        file.close();

    } else {
        exit(1);
    }
}

void printBox(int x0, int y0, int y1) {
    moveCursorTo(x0, y0);
    cout << char(201);
    for (int i = 0; i < y1 - y0 - 1; ++i) cout << char(205);
    cout << char(187);

    moveCursorTo(x0 + 3, y0);
    cout << char(200);
    for (int i = 0; i < y1 - y0 - 1; ++i) cout << char(205);
    cout << char(188);

    moveCursorTo(x0 + 1, y0); cout << char(186);
    moveCursorTo(x0 + 2, y0); cout << char(186);

    moveCursorTo(x0 + 1, y1); cout << char(186);
    moveCursorTo(x0 + 2, y1); cout << char(186);
}

void printStatus(int diamondsLeft, int timeLeft) {
    moveCursorTo(3, 10);
    cout << "- Diamonds left: " << diamondsLeft << ".  ";
    moveCursorTo(4, 10);
    cout << "- Time left: " << timeLeft / 60 << ':';
    timeLeft %= 60;
    if (timeLeft < 10) cout << 0;
    cout << timeLeft << ".  ";
}

void updateDiamonds(int diamondsLeft) {
    moveCursorTo(3, 10);
    cout << "- Diamonds left: " << diamondsLeft << ".  ";
}

void updateTimeLeft(int timeLeft) {
    moveCursorTo(4, 10);
    cout << "- Time left: " << timeLeft / 60 << ':';
    timeLeft %= 60;
    if (timeLeft < 10) cout << 0;
    cout << timeLeft << ".  ";
}

void printInstructions() {
    moveCursorTo(3, 85);
    cout << "- Controls: W, A, S, D || Stop/Quit: Esc.               ";
    moveCursorTo(4, 85);
    cout << "- Collect all the diamonds and find the way to the exit.";
}

void printAlert() {
    moveCursorTo(4, 85);
    cout << "- You haven't collected all the diamonds yet !!!        ";
}

void printSolvedTime(int solvedTime) {
    if (solvedTime / 60)
        cout << solvedTime / 60 << " minutes";
    if (solvedTime % 60) {
        if (solvedTime / 60) cout << ' ';
        cout << solvedTime % 60 << " seconds.    ";
    }
    else cout << '.';
}

void printWin(int solvedTime) {
    moveCursorTo(3, 85);
    cout << "Congratulations! Time taken: ";
    printSolvedTime(solvedTime);
    moveCursorTo(4, 85);
    cout << "Press 'Enter' to continue...                            ";
}

void printLose() {
    moveCursorTo(3, 85);
    cout << "Times up! Better luck next time...                      ";
    moveCursorTo(4, 85);
    cout << "Press 'Enter' to continue...                            ";
}

void printExit() {
    moveCursorTo(3, 85);
    cout << "Press Esc again to exit.                                ";
    moveCursorTo(4, 85);
    cout << "Or press any other key to return to the game.           ";
}

void updateTopScore(int solvedTime, int difficulty) {
    fstream file;
    if (!difficulty) file.open("./text/scores/beginner.txt");
    else if (difficulty == 1) file.open("./text/scores/intermediate.txt");
    else file.open("./text/scores/advanced.txt");

    if (file.is_open()) {
        int topScore;
        file >> topScore;
        file.clear();
        if (topScore > solvedTime) {
            file.seekp(0, ios::beg);
            file << solvedTime << "    ";
        }
        file.close();

    } else {
        exit(1);
    }
}
