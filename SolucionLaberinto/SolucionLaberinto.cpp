/*
* Main.cpp
*
*  Created on: Mar 20, 2015
*      Author: Ruben Jimenez Goni. Profesor Escuela de Computacion, Universidad de Costa Rica.
*/

#include "stdafx.h"
#include "Maze.h"

using namespace std;

int _tmain(int argc, _TCHAR* argv[]) {
	srand((unsigned int)time(0));

	int height = rand() % 20 + 20;
	int width = rand() % 20 + 20;

	// Se crea un laberinto aleatorio
	ofstream mazeFile("maze.txt");
	Maze maze(height, width);
	// Se guarda el laberinto en un archivo
	mazeFile << maze << endl;
	mazeFile.close();

	// Se lee un laberinto de un archivo
	ifstream mazeFileReaded("maze.txt");
	Maze mazeReaded(mazeFileReaded);

	// Se resuelve el laberinto leido del archivo
	ofstream mazeFileSolved("mazeFileSolved.txt");
	mazeReaded.solveMaze();
	mazeFileSolved << mazeReaded << endl;
	mazeFileSolved.close();

	cout << "END" << endl;

	return 0;
}

