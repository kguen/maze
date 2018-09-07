#include <ctime>
#include <fstream>
#include <conio.h>
#include <windows.h>
#include <mmsystem.h>
#include "maze.h"
#include "utils.h"
using namespace std;

int chosenTheme;
void selectTheme();
void selectDifficulty();
void selectMenu();
void printHighScores();

int main() {
	srand(time(NULL));
    PlaySound("./wav/on melancholy hill.wav", NULL, SND_FILENAME|SND_LOOP|SND_ASYNC);
	showCursor(false);
	selectMenu();
	return 0;
}

void selectMenu() {
	printBanner();
	printTxt("./text/menu.txt");

	int prevChoice = 0, currentChoice = 0;
	while (1) {
        if (prevChoice == 0) {
            moveCursorTo(21, 67);
            cout << ' ';
            moveCursorTo(21, 82);
            cout << ' ';

        } else if (prevChoice == 1) {
            moveCursorTo(24, 67);
            cout << ' ';
            moveCursorTo(24, 82);
            cout << ' ';

		} else if (prevChoice == 2) {
            moveCursorTo(27, 67);
            cout << ' ';
            moveCursorTo(27, 82);
            cout << ' ';

        } else {
            moveCursorTo(30, 67);
            cout << ' ';
            moveCursorTo(30, 82);
            cout << ' ';
        }
		if (currentChoice == 0) {
            moveCursorTo(21, 67);
            cout << char(16);
            moveCursorTo(21, 82);
            cout << char(17);

		} else if (currentChoice == 1) {
            moveCursorTo(24, 67);
            cout << char(16);
            moveCursorTo(24, 82);
            cout << char(17);

		} else if (currentChoice == 2) {
            moveCursorTo(27, 67);
            cout << char(16);
            moveCursorTo(27, 82);
            cout << char(17);

        } else {
            moveCursorTo(30, 67);
            cout << char(16);
            moveCursorTo(30, 82);
            cout << char(17);
        }
		char c = getch();
  		if (c == 's') {
            prevChoice = currentChoice;
  			currentChoice = (currentChoice + 1) % 4;
  		} else if (c == 'w') {
  		    prevChoice = currentChoice;
  			currentChoice = (currentChoice + 3) % 4;

		} else if (c == char(13)) {
			if (currentChoice == 0) {
				selectDifficulty();
			} else if (currentChoice == 1) {
				selectTheme();
			} else if (currentChoice == 2) {
                printHighScores();
			} else {
                break;
            }
		}
	}
}

void selectDifficulty() {
    system("cls");
    printBanner();
	printTxt("./text/difficulty.txt");
	int currentChoice = 0, prevChoice = 0;
	while (1) {
        if (prevChoice == 0) {
            moveCursorTo(21, 61);
            cout << ' ';
            moveCursorTo(21, 88);
            cout << ' ';

        } else if (prevChoice == 1) {
            moveCursorTo(24, 61);
            cout << ' ';
            moveCursorTo(24, 88);
            cout << ' ';

		} else if (prevChoice == 2) {
            moveCursorTo(27, 61);
            cout << ' ';
            moveCursorTo(27, 88);
            cout << ' ';

		} else {
			moveCursorTo(30, 61);
            cout << ' ';
            moveCursorTo(30, 88);
            cout << ' ';
		}
		if (currentChoice == 0) {
            moveCursorTo(21, 61);
            cout << char(16);
            moveCursorTo(21, 88);
            cout << char(17);

		} else if (currentChoice == 1) {
            moveCursorTo(24, 61);
            cout << char(16);
            moveCursorTo(24, 88);
            cout << char(17);

		} else if (currentChoice == 2) {
            moveCursorTo(27, 61);
            cout << char(16);
            moveCursorTo(27, 88);
            cout << char(17);

		} else {
			moveCursorTo(30, 61);
            cout << char(16);
            moveCursorTo(30, 88);
            cout << char(17);
        }
		char c = getch();
  		if (c == 's') {
            prevChoice = currentChoice;
  			currentChoice = (currentChoice + 1) % 4;
  		} else if (c == 'w') {
  		    prevChoice = currentChoice;
  			currentChoice = (currentChoice + 3) % 4;

		} else if (c == char(13)) {
			if (currentChoice == 0) {
				startGame(7, 18, 0, 90, chosenTheme);
			} else if (currentChoice == 1) {
				startGame(10, 27, 1, 150, chosenTheme);
			} else if (currentChoice == 2) {
				startGame(13, 35, 2, 240, chosenTheme);
			}
			break;
		}
	}
	setColor(15);
	system("cls");
	printBanner();
	printTxt("./text/menu.txt");
}

void selectTheme() {
    system("cls");
    printBanner();
	printTxt("./text/theme.txt");
	int currentChoice = 0, prevChoice = 0;
	while (1) {
		if (prevChoice == 0) {
            moveCursorTo(21, 65);
            cout << ' ';
            moveCursorTo(21, 85);
            cout << ' ';

        } else if (prevChoice == 1) {
            moveCursorTo(24, 65);
            cout << ' ';
            moveCursorTo(24, 85);
            cout << ' ';

		} else if (prevChoice == 2) {
            moveCursorTo(27, 65);
            cout << ' ';
            moveCursorTo(27, 85);
            cout << ' ';

		} else {
			moveCursorTo(30, 65);
            cout << ' ';
            moveCursorTo(30, 85);
            cout << ' ';
		}
		if (currentChoice == 0) {
            moveCursorTo(21, 65);
            cout << char(16);
            moveCursorTo(21, 85);
            cout << char(17);

		} else if (currentChoice == 1) {
            moveCursorTo(24, 65);
            cout << char(16);
            moveCursorTo(24, 85);
            cout << char(17);

		} else if (currentChoice == 2) {
            moveCursorTo(27, 65);
            cout << char(16);
            moveCursorTo(27, 85);
            cout << char(17);

		} else {
			moveCursorTo(30, 65);
            cout << char(16);
            moveCursorTo(30, 85);
            cout << char(17);
        }

		char c = getch();
  		if (c == 's') {
            prevChoice = currentChoice;
  			currentChoice = (currentChoice + 1) % 4;
  		} else if (c == 'w') {
  		    prevChoice = currentChoice;
  			currentChoice = (currentChoice + 3) % 4;

		} else if (c == char(13)) {
			if (currentChoice == 0) {
				chosenTheme = 0;
			} else if (currentChoice == 1) {
				chosenTheme = 1;
			} else if (currentChoice == 2) {
				chosenTheme = 2;
			} else {
				chosenTheme = 3;
			}
			break;
		}
	}
	system("cls");
	printBanner();
	printTxt("./text/menu.txt");
}

void printHighScores() {
    system("cls");
    printBanner();
    printTxt("./text/scores/template.txt");

    int score;
    ifstream file("./text/scores/beginner.txt");

    if (file.is_open()) {
        file >> score;
        if (score < 60 || score % 60 == 0) moveCursorTo(21, 65);
        else moveCursorTo(21, 60);

        cout << "Beginner: ";
        printSolvedTime(score);
        file.close();

    } else {
        exit(1);
    }
    file.open("./text/scores/intermediate.txt");
    if (file.is_open()) {
        file >> score;
        if (score < 60 || score % 60 == 0) moveCursorTo(24, 63);
        else moveCursorTo(24, 58);

        cout << "Intermediate: ";
        printSolvedTime(score);
        file.close();

    } else {
        exit(1);
    }
    file.open("./text/scores/advanced.txt");
    if (file.is_open()) {
        file >> score;
        if (score < 60 || score % 60 == 0) moveCursorTo(27, 65);
        else moveCursorTo(27, 60);

        cout << "Advanced: ";
        printSolvedTime(score);
        file.close();

    } else {
        exit(1);
    }
    while (!kbhit() || getch() != char(13));
    system("cls");
    printBanner();
    printTxt("./text/menu.txt");
}
