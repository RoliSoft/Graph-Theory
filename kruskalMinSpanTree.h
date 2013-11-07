#ifndef KRUSKAL_MIN_SPAN_TREE_H
#define KRUSKAL_MIN_SPAN_TREE_H

#include <unordered_map>
#include <vector>
#include "graph.h"
#include "algo.h"
#include "edge.h"

class KruskalMinSpanTree : public GraphAlgo
{
public:
	std::unordered_map<int, int> prep;
	std::vector<Edge*> tree;
	int weight;

	KruskalMinSpanTree(Graph* graph);

	void search();

private:
	void merge(int src, int dst);

protected:
	void printInfo();
};

#endif