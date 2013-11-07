#ifndef DEPTH_FIRST_SEARCH_REV_H
#define DEPTH_FIRST_SEARCH_REV_H

#include <unordered_set>
#include "graph.h"
#include "search.h"
#include "edge.h"

class DepthFirstSearch;

class DepthFirstSearchRev : public GraphSearch
{
public:
	int time;
	DepthFirstSearch* dfs;

	DepthFirstSearchRev(Graph* graph, DepthFirstSearch* dfs = nullptr);

	void search();

private:
	void discover(Vertex* vert);

protected:
	void printInfo();
};

#endif