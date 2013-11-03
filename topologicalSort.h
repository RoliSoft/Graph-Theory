#ifndef TOPOLOGICAL_SORT_H
#define TOPOLOGICAL_SORT_H

#include "graph.h"
#include "depthFirstSearch.h"

class TopologicalSort : public GraphAlgo
{
private:
	DepthFirstSearch* dfs;

public:
	TopologicalSort(Graph* graph);
	TopologicalSort(Graph* graph, DepthFirstSearch* dfs);

	void sort();
};

#endif