#ifndef HUNGARIAN_ALGORITHM_H
#define HUNGARIAN_ALGORITHM_H

#include <map>
#include <utility>
#include "graph.h"
#include "algo.h"
#include "edge.h"

class HungarianAlgorithm : public GraphAlgo
{
public:
	bool done;
	int step, num, rowZro, colZro, pathCnt;
	std::vector<std::vector<int>> cost, mask;
	std::vector<int> rowCvr, colCvr;
	std::vector<std::pair<int, int>> path;

	HungarianAlgorithm(Graph* graph);

	void search();
	void dump();

private:
	void findAndSubtractMin();
	void findAndMarkZero();
	void inspectMarkedZeroes();
	void findUnmarkedZero();
	void createInitialPath();
	void increaseLeftovers();

	void findZero(int& row, int& col);
	bool starInRow(int row);
	void findStarInRow(int row, int& col);
	void findStarInCol(int col, int& row);
	void findPrimeInRow(int row, int& col);
	void flipPathMask();
	void clearCovers();
	void removePrimes();
	void findSmallest(int& minVal);
};

#endif