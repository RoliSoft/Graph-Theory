#include <iostream>
#include <iomanip>
#include <limits>
#include <string>
#include "matrix.h"

_t Matrix<T>::Matrix()
{
}

_t Matrix<T>::Matrix(int n, int m, T def)
	: N(n),
	  M(m),
	  def(def),
	  data(std::vector<T>(n * m))
{
	std::fill(data.begin(), data.end(), def);
}

_t T Matrix<T>::get(int x, int y)
{
	return data[x * N + y];
}

_t void Matrix<T>::set(int x, int y, T val)
{
	data[x * N + y] = val;
}

_t void Matrix<T>::print()
{
	using namespace std;

	cout << endl;

	for (int i = 0; i < N; i++)
	{
		if (i == 0)
		{
			cout << "  " << left << setw(4) << (def == numeric_limits<T>::max() ? "inf" : " " + to_string(def)) << right;

			for (int j = 0; j < M; j++)
			{
				cout << setw(3) << (j + 1) << " ";
			}

			cout << endl << "     +";

			for (int j = 0; j < M; j++)
			{
				cout << " -- ";
			}

			cout << endl;
		}

		cout << "  " << setw(2) << (i + 1) << " |";

		for (int j = 0; j < M; j++)
		{
			auto val = get(i, j);

			if (val == def)
			{
				cout << "  - ";
			}
			else
			{
				cout << setw(3) << val << " ";
			}
		}

		cout << endl;
	}

	cout << endl;
}

template class Matrix<int>;
template class Matrix<bool>;