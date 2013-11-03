#ifndef MATRIX_H
#define MATRIX_H

#include <vector>
#include <algorithm>

#ifndef _t
#define _t template <typename T>
#endif

_t class Matrix
{
private:
	T def;
	std::vector<T> data;

public:
	int N, M;

	Matrix();
	Matrix(int n, int m, T def);

	T get(int x, int y);
	void set(int x, int y, T val);
	void print();
};

#endif