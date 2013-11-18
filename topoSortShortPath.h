#ifndef TOPO_SORT_SHORT_PATH_H
#define TOPO_SORT_SHORT_PATH_H

#include <unordered_map>
#include "graph.h"
#include "shortPath.h"
#include "edge.h"

class DepthFirstSearch;

class TopoSortShortPath : public GraphShortPath
{
public:
	std::unordered_map<Vertex*, int> distance;
	std::unordered_map<Vertex*, Vertex*> previous;
	Vertex* source;
	DepthFirstSearch* dfs;

	TopoSortShortPath(Graph* graph, DepthFirstSearch* dfs = nullptr);

	void search(Vertex* source = nullptr);
	void dump();
};

#endif