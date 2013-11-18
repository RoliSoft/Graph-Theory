#ifndef AUTO_SHORT_PATH_H
#define AUTO_SHORT_PATH_H

#include "graph.h"
#include "algo.h"

class DepthFirstSearch;

class AutoShortPath : public GraphAlgo
{
public:
	DepthFirstSearch* dfs;

	AutoShortPath(Graph* graph, DepthFirstSearch* dfs = nullptr);

	void search(Vertex* source = nullptr);
	void dump();

private:
	void* _algo;
};

#endif