/*
 * Laberinto.cpp
 *
 *  Created on: Mar 20, 2015
 *      Author: Ruben Jimenez Goni. Profesor Escuela de Computacion, Universidad de Costa Rica.
 */

#include "stdafx.h"
#include "Maze.h"

const int Maze::NI[4] = {-1, 1, 0, 0};
const int Maze::NJ[4] = {0, 0, -1, 1};

const int Maze::CORNER_TL[NEIGHBOORS] = {EMPTY, EMPTY, EMPTY, EMPTY, WALL, WALL, EMPTY, WALL, EMPTY}; // ╔
const int Maze::CORNER_TR[NEIGHBOORS] = {EMPTY, EMPTY, EMPTY, WALL, WALL, EMPTY, EMPTY, WALL, EMPTY}; // ╗
const int Maze::CORNER_BL[NEIGHBOORS] = {EMPTY, WALL, EMPTY, EMPTY, WALL, WALL, EMPTY, EMPTY, EMPTY}; // ╚
const int Maze::CORNER_BR[NEIGHBOORS] = {EMPTY, WALL, EMPTY, WALL, WALL, EMPTY, EMPTY, EMPTY, EMPTY}; // ╝
const int Maze::BAR_H[NEIGHBOORS] = {ANY, EMPTY, ANY, ANY, WALL, ANY, ANY, EMPTY, ANY}; // ═
const int Maze::BAR_V[NEIGHBOORS] = {ANY, ANY, ANY, EMPTY, WALL, EMPTY, ANY, ANY, ANY}; // ║
const int Maze::PIPE_L[NEIGHBOORS] = {EMPTY, WALL, EMPTY, WALL, WALL, EMPTY, EMPTY, WALL, EMPTY}; // ╣
const int Maze::PIPE_R[NEIGHBOORS] = {EMPTY, WALL, EMPTY, EMPTY, WALL, WALL, EMPTY, WALL, EMPTY}; // ╠
const int Maze::PIPE_B[NEIGHBOORS] = {EMPTY, EMPTY, EMPTY, WALL, WALL, WALL, EMPTY, WALL, EMPTY}; // ╦
const int Maze::PIPE_T[NEIGHBOORS] = {EMPTY, WALL, EMPTY, WALL, WALL, WALL, EMPTY, EMPTY, EMPTY}; // ╩
const int Maze::CROSS[NEIGHBOORS] = {EMPTY, WALL, EMPTY, WALL, WALL, WALL, EMPTY, WALL, EMPTY}; // ╬

const int * Maze::PATTERNS[PATTERNS_NUMBER] = {&CORNER_TL[0], &CORNER_TR[0], &CORNER_BL[0], &CORNER_BR[0], &BAR_H[0], &BAR_V[0], &PIPE_L[0], &PIPE_R[0], &PIPE_B[0], &PIPE_T[0], &CROSS[0]};

const char * Maze::SYMBOLS[PATTERNS_NUMBER] = {"╔", "╗", "╚", "╝", "═", "║", "╣", "╠", "╦", "╩", "╬"};

Maze::Maze(istream & in) :
height(0), width(0), maze(0), iEntry(0), jEntry(0), iExit(0), jExit(0) {
	in >> *this;
}

Maze::Maze(int n, int w) {
	this->height = n * 2 + 1;
	this->width = w * 2 + 1;
	this->maze = new int *[this->height];
	for (int i = 0; i < this->height; ++i) {
		this->maze[i] = new int[this->width];
		for (int j = 0; j < this->width; ++j) {
			if (i % 2 == 1 && j % 2 == 1) {
				this->maze[i][j] = EMPTY;
			} else {
				this->maze[i][j] = WALL;
			}
		}
	}

	bool topEntry = rand() % 2 == 0;

	int i = 0, j = 0;
	if (topEntry) {
		j = rand() % w * 2 + 1;
	} else {
		i = rand() % n * 2 + 1;
	}

	// Entrada
	iEntry = i, jEntry = j;
	this->maze[i][j] = EMPTY;

	// Construcción de mazo
	if (topEntry) {
		this->buildMaze(1, j);
	} else {
		this->buildMaze(i, 1);
	}

	i = n * 2, j = w * 2;
	if (topEntry) {
		j = rand() % w * 2 + 1;
	} else {
		i = rand() % n * 2 + 1;
	}

	// Salida
	iExit = i, jExit = j;
	this->maze[i][j] = EMPTY;

	this->unvisitMaze();
}

Maze::~Maze() {
	if (maze != 0) {
		for (int i = 0; i < height; ++i) {
			for (int j = 0; j < width; ++j) {
				maze[i][j] = 0;
			}
			maze[i] = 0;
			delete maze[i];
		}
		delete maze;
	}
}

void Maze::buildMaze(int i, int j) {
	if (maze[i][j] != VISITED) {
		maze[i][j] = VISITED;
		int tmp[4] = {0, 1, 2, 3};
		for (int k = 0; k < 20; ++k) {
			swap(tmp[rand() % 4], tmp[rand() % 4]);
		}
		for (int k = 0; k < 4; ++k) {
			int iN = i + NI[tmp[k]] * 2;
			int jN = j + NJ[tmp[k]] * 2;
			if (validPosition(iN, jN) && maze[iN][jN] == EMPTY) {
				int iW = (i + iN) / 2;
				int jW = (j + jN) / 2;
				maze[iW][jW] = EMPTY;
				buildMaze(iN, jN);
			}
		}
	}
}

void Maze::solveMaze() {
	if (solveMazeR(iEntry, jEntry)) {
		cout << "Maze Exit Found" << endl;
	} else {
		cout << "Maze Exit Not Found" << endl;
	}
	unvisitMaze();
}

bool Maze::solveMazeR(int i, int j) {
	bool pathToExitFound = false;
	if (i == iExit && j == jExit) {
		pathToExitFound = true;
		maze[i][j] = SOLUTION;
	} else {
		if (maze[i][j] != VISITED) {
			maze[i][j] = VISITED;
			for (int k = 0; k < 4; ++k) {
				int iN = i + NI[k];
				int jN = j + NJ[k];
				if (validPosition(iN, jN) && maze[iN][jN] == EMPTY
					&& solveMazeR(iN, jN)) {
					maze[i][j] = SOLUTION;
					pathToExitFound = true;
				}
			}
		}
	}
	return pathToExitFound;
}

void Maze::unvisitMaze() {
	for (int i = 1; i < height; i++) {
		for (int j = 1; j < width; j++) {
			if (maze[i][j] == VISITED) {
				maze[i][j] = EMPTY;
			}
		}
	}
}

bool Maze::validPosition(int i, int j) const {
	return 0 <= i && 0 <= j && i < height && j < width;
}

int Maze::identifyPattern(int i, int j) const {
	int * neighboors = extractNeighboors(i, j);
	bool match = false;
	int n = 0;
	while (n < PATTERNS_NUMBER && !match) {
		match = true;
		for (int m = 0; m < NEIGHBOORS && match; ++m) {
			match = PATTERNS[n][m] == ANY || neighboors[m] == PATTERNS[n][m];
		}
		if (!match) {
			++n;
		}
	}
	if (!match) {
		n = -1;
	}
	delete neighboors;
	return n;
}

int * Maze::extractNeighboors(int i, int j) const {
	int k = 0;
	int * neighboors = new int[NEIGHBOORS];
	for (int n = -1; n <= 1; ++n) {
		for (int m = -1; m <= 1; ++m) {
			if (validPosition(i + n, j + m)) {
				switch (maze[i + n][j + m]) {
				case WALL:
					neighboors[k++] = WALL;
					break;
				case EMPTY:
				case SOLUTION:
				case VISITED:
				default:
					neighboors[k++] = EMPTY;
					break;
				}
			} else {
				neighboors[k++] = EMPTY;
			}
		}
	}
	return neighboors;
}

ostream & operator<<(ostream & out, const Maze & maze) {
	out << ((maze.height - 1) / 2) << " " << ((maze.width - 1) / 2) << endl;
	for (int i = 0; i < maze.height; ++i) {
		for (int j = 0; j < maze.width; ++j) {
			int pattern = maze.identifyPattern(i, j);
			if (pattern != -1) {
				out << maze.SYMBOLS[pattern];
			} else {
				switch (maze.maze[i][j]) {
				case Maze::EMPTY:
				case Maze::VISITED:
				default:
					out << " ";
					break;
				case Maze::SOLUTION:
					out << "*";
					break;
				}
			}
		}
		out << endl;
	}
	return out;
}

istream & operator>>(istream & in, Maze & maze) {
	int n, m;
	in >> n >> m;
	maze.height = n * 2 + 1;
	maze.width = m * 2 + 1;
	int max = maze.width * 3 + 2; // Cada caracter puede usar hasta 3 bytes por lo visto en clase más 2 caracteres de cambio de línea
	char * str = Util::zeroVector(new char[max], max);
	in.getline(str, n); // Se termina de leer la línea actual
	maze.maze = new int *[maze.height];
	for (int i = 0; i < maze.height; i++) {
		Util::zeroVector(new char[max], max);
		in.getline(str, max);
		maze.maze[i] = new int[maze.width];
		int j = 0, k = 0;
		while (k < max && str[k] != 0) {
			if (str[k] == ' ') {
				if (i == 0 || j == 0) {
					maze.iEntry = i;
					maze.jEntry = j;
				}
				if (i == maze.height - 1 || j == maze.width - 1) {
					maze.iExit = i;
					maze.jExit = j;
				}
				maze.maze[i][j++] = maze.EMPTY;
				k++;
			} else {
				maze.maze[i][j++] = maze.WALL;
				k += 3;
			}
		}
	}
	delete str;
	return in;
}
