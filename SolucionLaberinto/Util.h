/*
 * Util.h
 *
 *  Created on: Apr 1, 2015
 *      Author: Ruben Jimenez Goni. Profesor Escuela de Computacion, Universidad de Costa Rica.
 */

#pragma once

#include "stdafx.h"

using namespace std;

class Util {

public:

	template<class T> static void swap(T & a, T & b) {
		T tmp = a;
		a = b;
		b = tmp;
	}

	template<class T> static void printVector(T * v, int n, bool endln) {
		for (int i = 0; i < n; ++i) {
			cout << v[i] << " ";
		}
		if (endln) {
			cout << endl;
		}
	}

	template<class T> static T * zeroVector(T * v, int n) {
		for (int i = 0; i < n; ++i) {
			v[i] = 0;
		}
		return v;
	}

};
