#ifndef AUTO_SHORT_PATH_H
#define AUTO_SHORT_PATH_H

#include "graph.h"
#include "shortPath.h"

class DepthFirstSearch;

class AutoShortPath : public GraphShortPath
{
public:
	GraphShortPath* algo;
	DepthFirstSearch* dfs;

	AutoShortPath(Graph* graph, DepthFirstSearch* dfs = nullptr);

	void search(Vertex* source = nullptr);
	void dump();
};

#endif