/*
 * Laberinto.h
 *
 *  Created on: Mar 20, 2015
 *      Author: Ruben Jimenez Goni. Profesor Escuela de Computacion, Universidad de Costa Rica.
 */

#pragma once

#include "stdafx.h"
#include "Util.h"

using namespace std;

class Maze {

	friend ostream & operator<<(ostream & out, const Maze & maze);
	friend istream & operator>>(istream & out, Maze & maze);

private:

	static const int EMPTY = 0;
	static const int SOLUTION = 1;
	static const int WALL = 2;
	static const int VISITED = 3;
	static const int ANY = 4;

	static const int PATTERNS_NUMBER = 11;
	static const int NEIGHBOORS = 9;

	// 0=Arriba, 1=Abajo, 2=Izquierda, 3=Derecha
	static const int NI[4];
	static const int NJ[4];

	// 0=Nada, 1=Pared
	static const int CORNER_TL[NEIGHBOORS]; // ╔
	static const int CORNER_TR[NEIGHBOORS]; // ╗
	static const int CORNER_BL[NEIGHBOORS]; // ╚
	static const int CORNER_BR[NEIGHBOORS]; // ╝
	static const int BAR_H[NEIGHBOORS]; // ═
	static const int BAR_V[NEIGHBOORS]; // ║
	static const int PIPE_L[NEIGHBOORS]; // ╣
	static const int PIPE_R[NEIGHBOORS]; // ╠
	static const int PIPE_B[NEIGHBOORS]; // ╦
	static const int PIPE_T[NEIGHBOORS]; // ╩
	static const int CROSS[NEIGHBOORS]; // ╬
	static const int * PATTERNS[PATTERNS_NUMBER];
	static const char * SYMBOLS[PATTERNS_NUMBER];

	int height, width;
	int ** maze;

	int iEntry, jEntry;
	int iExit, jExit;
public:
	Maze(istream &);
	Maze(int, int);
	virtual ~Maze();

	void solveMaze();

private:
	void buildMaze(int, int);
	bool solveMazeR(int, int);
	void unvisitMaze();
	bool validPosition(int, int) const;
	int identifyPattern(int i, int j) const;
	int * extractNeighboors(int i, int j) const;

};

ostream & operator<<(ostream &, const Maze &);
istream & operator>>(istream &, Maze &);
