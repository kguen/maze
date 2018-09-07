#ifndef MAZE_HPP
#define MAZE_HPP
#include <iostream>
#include <vector>
using namespace std;

class ColorSet {
public:
	int background;
	int walls;
	int diamonds;
	int entranceDoor;
	int exitDoor;
	int player;
	int text;

	ColorSet() {};
	ColorSet(int background, int walls, int diamonds, int entranceDoor, int exitDoor, int player, int text):
		background(background),
		walls(walls),
		diamonds(diamonds),
		entranceDoor(entranceDoor),
		exitDoor(exitDoor),
		player(player),
		text(text) {}
};

class Cell {
public:
    int x, y;
    bool visited;

    Cell() {}
    Cell(int x, int y): x(x), y(y) {
    	visited = 0;
    }
};

class Maze {
private:
	int Rows, Cols;
	int ShiftX, ShiftY;
	int difficulty;

	vector <vector <Cell>> cells;
	vector <vector <int>> state;

	void dfs(int, int);

public:
	ColorSet COLOR;

	int diamondsLeft;
	int timeLimit;

	Maze(int, int, int, int, int);
	void generate();
	void startGame();
};

#endif