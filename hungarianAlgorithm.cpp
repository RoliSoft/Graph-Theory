#include <boost/range/adaptor/map.hpp>
#include "hungarianAlgorithm.h"

HungarianAlgorithm::HungarianAlgorithm(Graph* graph)
	: GraphAlgo(graph),
	  done(false),
	  step(1),
	  rowZro(-1),
	  colZro(-1),
	  pathCnt(0),
	  num(graph->verts.size() / 2),
	  cost(std::vector<std::vector<int>>(num)),
	  mask(std::vector<std::vector<int>>(num)),
	  rowCvr(std::vector<int>(num)),
	  colCvr(std::vector<int>(num)),
	  path(std::vector<std::pair<int, int>>((num + 1) * 2))
{
	for (int i = 0; i < num; i++)
	{
		cost[i] = std::vector<int>(cost.size());
		mask[i] = std::vector<int>(cost.size());

		for (int j = 0; j < num; j++)
		{
			cost[i][j] = graph->weightrix.at_element(i + cost.size() + 1, j + 1);
			mask[i][j] = 0;
		}
	}

	for (int i = 0; i < (num + 1) * 2; i++)
	{
		path[i] = std::make_pair(0, 0);
	}
}

void HungarianAlgorithm::search()
{
	using namespace std;

	while (!done)
	{
		for (int i = 0; i < num; i++)
		{
			for (int j = 0; j < num; j++)
			{
				cout << " " << cost[i][j];
			}

			cout << endl;
		}

		cout << endl;

		for (int i = 0; i < num; i++)
		{
			for (int j = 0; j < num; j++)
			{
				cout << " " << mask[i][j];
			}

			cout << endl;
		}

		cout << endl;

		switch (step)
		{
		case 1: findAndSubtractMin(); break;
		case 2: findAndMarkZero(); break;
		case 3: inspectMarkedZeroes(); break;
		case 4: findUnmarkedZero(); break;
		case 5: createInitialPath(); break;
		case 6: increaseLeftovers(); break;
		case 7: done = true; break;
		}
	}
}

void HungarianAlgorithm::dump()
{
	using namespace std;

	cout << " Hungarian algorithm:" << endl;
	cout << endl << endl;
}

void HungarianAlgorithm::findAndSubtractMin()
{
	int rowMin;

	for (int r = 0; r < num; r++)
	{
		rowMin = cost[r][0];

		for (int c = 0; c < num; c++)
		{
			if (cost[r][r] < rowMin)
			{
				rowMin = cost[r][c];
			}
		}

		for (int c = 0; c < num; c++)
		{
			cost[r][c] -= rowMin;
		}
	}

	step = 2;
}

void HungarianAlgorithm::findAndMarkZero()
{
	for (int r = 0; r < num; r++)
	{
		for (int c = 0; c < num; c++)
		{
			if (cost[r][c] == 0 && rowCvr[r] == 0 && colCvr[c] == 0)
			{
				mask[r][c] = 1;
				rowCvr[r] = 1;
				colCvr[c] = 1;
			}
		}
	}

	for (int i = 0; i < num; i++)
	{
		rowCvr[i] = 0;
		colCvr[i] = 0;
	}

	step = 3;
}

void HungarianAlgorithm::inspectMarkedZeroes()
{
	for (int r = 0; r < num; r++)
	{
		for (int c = 0; c < num; c++)
		{
			if (mask[r][c] == 1)
			{
				colCvr[c] = 1;
			}
		}
	}

	int colCnt = 0;

	for (int c = 0; c < num; c++)
	{
		if (colCvr[c] == 1)
		{
			colCnt++;
		}
	}

	if (colCnt >= num)
	{
		step = 7;
	}
	else
	{
		step = 4;
	}
}

void HungarianAlgorithm::findUnmarkedZero()
{
	int r = -1, c = -1;
	bool done = false;

	while (!done)
	{
		findZero(r, c);

		if (r == -1)
		{
			done = true;
			step = 6;
		}
		else
		{
			mask[r][c] = 2;

			if (starInRow(r))
			{
				findStarInRow(r, c);
				rowCvr[r] = 1;
				colCvr[c] = 0;
			}
			else
			{
				done = true;
				step = 5;
				rowZro = r;
				colZro = c;
			}
		}
	}
}

void HungarianAlgorithm::createInitialPath()
{
	int r = -1, c = -1;
	bool done = false;

	pathCnt = 1;
	path[pathCnt - 1].first  = rowZro;
	path[pathCnt - 1].second = colZro;

	while (!done)
	{
		findStarInCol(path[pathCnt - 1].second, r);

		if (r > -1)
		{
			pathCnt++;
			path[pathCnt - 1].first  = r;
			path[pathCnt - 1].second = path[pathCnt - 2].second;
		}
		else
		{
			done = true;
		}

		if (!done)
		{
			findPrimeInRow(path[pathCnt - 1].first, c);

			pathCnt++;
			path[pathCnt - 1].first  = path[pathCnt - 2].first;
			path[pathCnt - 1].second = c;
		}
	}

	flipPathMask();
	clearCovers();
	removePrimes();

	step = 3;
}

void HungarianAlgorithm::increaseLeftovers()
{
	int minVal = INT_MAX;
	findSmallest(minVal);

	for (int r = 0; r < num; r++)
	{
		for (int c = 0; c < num; c++)
		{
			if (rowCvr[r] == 1)
			{
				cost[r][c] += minVal;
			}

			if (colCvr[c] == 0)
			{
				cost[r][c] -= minVal;
			}
		}
	}

	step = 4;
}

void HungarianAlgorithm::findZero(int& row, int& col)
{
	int r = 0, c = 0;
	bool done = false;

	row = -1;
	col = -1;

	while (!done)
	{
		c = 0;

		bool done2 = false;
		while (!done2)
		{
			if (cost[r][c] == 0 && rowCvr[r] == 0 && colCvr[c] == 0)
			{
				row = r;
				col = c;
				done = true;
			}

			c++;

			if (c >= num || done)
			{
				done2 = true;
			}
		}

		r++;

		if (r >= num)
		{
			done = true;
		}
	}
}

bool HungarianAlgorithm::starInRow(int row)
{
	for (int c = 0; c < num; c++)
	{
		if (mask[row][c] == 1)
		{
			return true;
		}
	}

	return false;
}

void HungarianAlgorithm::findStarInRow(int row, int& col)
{
	col = -1;

	for (int c = 0; c < num; c++)
	{
		if (mask[row][c] == 1)
		{
			col = c;
			return;
		}
	}
}

void HungarianAlgorithm::findStarInCol(int col, int& row)
{
	row = -1;

	for (int r = 0; r < num; r++)
	{
		if (mask[r][col] == 1)
		{
			row = r;
		}
	}
}

void HungarianAlgorithm::findPrimeInRow(int row, int& col)
{
	for (int c = 0; c < num; c++)
	{
		if (mask[row][c] == 2)
		{
			col = c;
		}
	}
}

void HungarianAlgorithm::flipPathMask()
{
	for (int p = 0; p < pathCnt; p++)
	{
		mask[path[p].first][path[p].second] += 1;
		mask[path[p].first][path[p].second] %= 2;
	}
}

void HungarianAlgorithm::clearCovers()
{
	for (int i = 0; i < num; i++)
	{
		rowCvr[i] = 0;
		colCvr[i] = 0;
	}
}

void HungarianAlgorithm::removePrimes()
{
	for (int r = 0; r < num; r++)
	{
		for (int c = 0; c < num; c++)
		{
			if (mask[r][c] == 2)
			{
				mask[r][c] = 0;
			}
		}
	}
}

void HungarianAlgorithm::findSmallest(int& minVal)
{
	for (int r = 0; r < num; r++)
	{
		for (int c = 0; c < num; c++)
		{
			if (rowCvr[r] == 0 && colCvr[c] == 0)
			{
				if (minVal > cost[r][c])
				{
					minVal = cost[r][c];
				}
			}
		}
	}
}