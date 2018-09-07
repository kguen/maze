#ifndef UTILS_HPP
#define UTILS_HPP

void moveCursorTo(short, short);
void setColor(int);
void showCursor(bool);

void startGame(int, int, int, int, int);

void printBanner();
void printTxt(const char * s);
void printInstructions();

void printBox(int, int, int);
void printStatus(int, int);
void updateDiamonds(int);
void updateTimeLeft(int);

void printAlert();
void printSolvedTime(int);
void printWin(int);
void printLose();
void printExit();
void updateTopScore(int, int);

#endif
