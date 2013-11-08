#ifndef KRUSKAL_MIN_SPAN_TREE_H
#define KRUSKAL_MIN_SPAN_TREE_H

#include <vector>
#include "graph.h"
#include "algo.h"
#include "edge.h"

class KruskalMinSpanTree : public GraphAlgo
{
public:
	std::vector<Edge*> tree;
	int weight;

	KruskalMinSpanTree(Graph* graph);

	void search();
	void dump();
};

#endif