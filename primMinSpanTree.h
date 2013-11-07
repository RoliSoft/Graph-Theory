#ifndef PRIM_MIN_SPAN_TREE_H
#define PRIM_MIN_SPAN_TREE_H

#include <vector>
#include "graph.h"
#include "algo.h"
#include "edge.h"

class PrimMinSpanTree : public GraphAlgo
{
public:
	std::vector<Edge*> tree;
	int weight;

	PrimMinSpanTree(Graph* graph);

	void search();

protected:
	void printInfo();
};

#endif