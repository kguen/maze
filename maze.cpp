#include <iostream>
#include <vector>
#include <conio.h>
#include <windows.h>
#include <chrono>
#include <thread>

#include "maze.h"
#include "utils.h"
using namespace std;

const int gameScrH = 30, gameScrW = 150;

const int dx[] = {0, 1, 0, -1};
const int dy[] = {1, 0, -1, 0};

const ColorSet DEFAULT(7, 15, 14, 12, 10, 11, 10),
ALIEN_BLUE(23, 27, 30, 28, 26, 29, 31),
MY_LITTLE_PONY(87, 93, 86, 84, 82, 87, 93),
TREES(39, 42, 46, 38, 35, 42, 42);

Maze::Maze(int Rows, int Cols, int timeLimit, int difficulty, int colorID) {
	this->Rows = Rows;
	this->Cols = Cols;
	cells.assign(Rows, vector <Cell>(Cols));
	state.assign(Rows * 2 + 1, vector <int>(Cols * 2 + 1, 0));
	diamondsLeft = 0;
    this->timeLimit = timeLimit;
    this->difficulty = difficulty;

    if (colorID == 0) {
        COLOR = DEFAULT;
    } else if (colorID == 1) {
        COLOR = ALIEN_BLUE;
    } else if (colorID == 2) {
        COLOR = MY_LITTLE_PONY;
    } else {
        COLOR = TREES;
    }
    ShiftX = (36 - gameScrH) + (gameScrH - (Rows * 2 + 1)) / 2;
    ShiftY = gameScrW / 2 - (Cols * 2 + 1);

	for (int i = 0; i < Rows; ++i) {
		for (int j = 0; j < Cols; ++j) {
			cells[i][j] = Cell(ShiftX + i * 2 + 1, ShiftY + j * 4 + 2);
		}
	}
	setColor(COLOR.background);
    system("cls");
}

void Maze::dfs(int x, int y) {
	int curX = 0, curY = 0;
	vector <int> StackX, StackY;

    int cellsVisited = 0;
    int sleepDuration = 25;

	while (1) {
        if (kbhit() && getch() == char(13)) {
            sleepDuration = 0;
        }
        bool newCell = 0;
        moveCursorTo(cells[curX][curY].x, cells[curX][curY].y);
        setColor(COLOR.player);
        cout << char(254);
        moveCursorTo(cells[curX][curY].x, cells[curX][curY].y);
        cout << ' ';
        this_thread::sleep_for(chrono::milliseconds(sleepDuration));

        if (!cells[curX][curY].visited) {
            ++cellsVisited;
            newCell = 1;
            cells[curX][curY].visited = 1;
            state[curX * 2 + 1][curY * 2 + 1] = 1;

            moveCursorTo(3, 67);
            setColor(COLOR.walls);
            cout << "Maze generating: " << 100 * cellsVisited / (Rows * Cols) << "%.";
        }
		vector <int> neighbors;
		for (int i = 0; i < 4; ++i) {
			int nextX = curX + dx[i];
			int nextY = curY + dy[i];

			if (nextX < 0 || nextY < 0 || nextX >= Rows || nextY >= Cols) continue;
			if (cells[nextX][nextY].visited) continue;

			neighbors.push_back(i);
		}
		if (neighbors.empty()) {
            if (newCell && curX != Rows - 1 && curY != Cols - 1) {
                if (rand() % 4 == 0) {
                    moveCursorTo(cells[curX][curY].x, cells[curX][curY].y);
                    state[curX * 2 + 1][curY * 2 + 1] = 2;
                    ++diamondsLeft;
                    setColor(COLOR.diamonds);
                    cout << char(260);
                }
            }
			if (StackX.size()) {
                int newX = StackX.back();
                int newY = StackY.back();
                StackX.pop_back();
                StackY.pop_back();

                int index = 0;
                if (newX - curX == 1) index = 1;
                else if (curY - newY == 1) index = 2;
                else if (curX - newX == 1) index = 3;

                moveCursorTo(cells[curX][curY].x + dx[index], cells[curX][curY].y + dy[index] * 2);
                setColor(COLOR.player);
                cout << char(254);
                this_thread::sleep_for(chrono::milliseconds(sleepDuration));
                moveCursorTo(cells[curX][curY].x + dx[index], cells[curX][curY].y + dy[index] * 2);
                cout << ' ';

			 	curX = newX;
				curY = newY;
				continue;
			}
			break;
		}
		StackX.push_back(curX);
		StackY.push_back(curY);

		int index = neighbors[rand() % neighbors.size()];
		moveCursorTo(cells[curX][curY].x + dx[index], cells[curX][curY].y + dy[index] * 2);
        setColor(COLOR.player);
        cout << char(254);
		this_thread::sleep_for(chrono::milliseconds(sleepDuration));
        moveCursorTo(cells[curX][curY].x + dx[index], cells[curX][curY].y + dy[index] * 2);
        cout << ' ';

		state[curX * 2 + 1 + dx[index]][curY * 2 + 1 + dy[index]] = 1;
		curX += dx[index];
		curY += dy[index];
	}
}

void Maze::generate() {
    setColor(COLOR.walls);
	for (int i = 0; i < Rows * 2 + 1; ++i) {
		moveCursorTo(i + ShiftX, ShiftY);
		for (int j = 0; j < Cols * 2 + 1; ++j) {
			cout << char(254) << ' ';
		}
	}
    moveCursorTo(4, 60);
    cout << "Press 'Enter' to skip visualizing.";
	dfs(0, 0);
    this_thread::sleep_for(chrono::milliseconds(50));
    moveCursorTo(3, 67);
    cout << "                                  ";
    moveCursorTo(4, 60);
    cout << "                                  ";

	setColor(COLOR.walls);
	for (int i = 0; i < Rows * 2 + 1; ++i) {
		for (int j = 0; j < Cols * 2 + 1; ++j) if (!state[i][j]) {
            int x = i + ShiftX;
            int y = j * 2 + ShiftY;
            moveCursorTo(x, y);
            cout << char(177);

            if (j < Cols * 2 && !state[i][j - 1] && !state[i][j + 1]) {
                moveCursorTo(x, y - 1);
                cout << char(177);
                moveCursorTo(x, y + 1);
                cout << char(177);
            }
		}
        this_thread::sleep_for(chrono::milliseconds(25));
	}
	moveCursorTo(ShiftX + 1, ShiftY);
	setColor(COLOR.entranceDoor);
	cout << char(178);
	moveCursorTo(cells[Rows - 1][Cols - 1].x, cells[Rows - 1][Cols - 1].y + 2);
	setColor(COLOR.exitDoor);
	cout << char(178);
	state[Rows * 2 - 1][Cols * 2] = 1;

    setColor(COLOR.walls);
    printBox(2, 8, 32); // status box
    printBox(2, 83, 142); // alert box

    setColor(COLOR.text);
    printInstructions();
    updateDiamonds(diamondsLeft);
    updateTimeLeft(timeLimit);
}

void Maze::startGame() {
    int playerX = 1, playerY = 1;
    setColor(COLOR.player);
    moveCursorTo(ShiftX + playerX, ShiftY + playerY * 2);
    cout << char(254);

    int prevX = 1, prevY = 1;
    int prevTimeLeft = timeLimit;
    int win = -1;

    clock_t beginTime = clock();
    clock_t delay = 0;

    while(1) {
        if (prevX != playerX || prevY != playerY) {
            moveCursorTo(ShiftX + prevX, ShiftY + prevY * 2);
            cout << ' ';
            setColor(COLOR.player);
            moveCursorTo(ShiftX + playerX, ShiftY + playerY * 2);
            cout << char(254);
        }
        if (state[playerX][playerY] == 2) {
            --diamondsLeft;
            setColor(COLOR.text);
            updateDiamonds(diamondsLeft);
            state[playerX][playerY] = 1;
        }
        if (playerX == Rows * 2 - 1 && playerY == Cols * 2 && !diamondsLeft) {
            win = 1;
            break;
        }
        int timeLeft = timeLimit - (clock() - beginTime - delay) / CLOCKS_PER_SEC;

        if (prevTimeLeft != timeLeft) {
            setColor(COLOR.text);
            updateTimeLeft(timeLeft);
            prevTimeLeft = timeLeft;
        }
        if (!timeLeft) {
            win = 0;
            break;
        }
        prevX = playerX;
        prevY = playerY;

        if (kbhit()) {
            char c = getch();
            if (c == 'w' && playerX > 0 && state[playerX - 1][playerY]) --playerX;
            if (c == 's' && playerX < Rows * 2 && state[playerX + 1][playerY]) ++playerX;
            if (c == 'a' && playerY > 0 && state[playerX][playerY - 1]) --playerY;
            if (c == 'd' && playerY < Cols * 2 && state[playerX][playerY + 1]) ++playerY;

            if (c == char(27)) {
                setColor(COLOR.text);
                printExit();
                bool chooseExit = 0;

                clock_t startDelay = clock();
                while (1) {
                    if (kbhit()) {
                        if (getch() == char(27)) chooseExit = 1;
                        break;
                    }
                }
                delay += clock() - startDelay;
                if (chooseExit == 1) break;
                else printInstructions();
            }
            if (playerX == Rows * 2 - 1 && playerY == Cols * 2 && diamondsLeft) {
                setColor(COLOR.text);
                printAlert();
                playerX = prevX;
                playerY = prevY;
            }
        }
    }
    if (win == 1) {
        int solvedTime = (clock() - beginTime) / CLOCKS_PER_SEC;

        setColor(COLOR.text);
        printWin(solvedTime);
        updateTopScore(solvedTime, difficulty);
        while (!kbhit() || getch() != char(13));

    } else if (win == 0) {
        printLose();
        while (!kbhit() || getch() != char(13));
    }
}
