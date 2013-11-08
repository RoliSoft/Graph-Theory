#ifndef BELLMAN_FORD_SHORT_PATH_H
#define BELLMAN_FORD_SHORT_PATH_H

#include <unordered_map>
#include "graph.h"
#include "algo.h"
#include "edge.h"

class BellmanFordShortPath : public GraphAlgo
{
public:
	std::unordered_map<Vertex*, int> distance;
	std::unordered_map<Vertex*, Vertex*> previous;
	Vertex* source;
	bool negCycle;

	BellmanFordShortPath(Graph* graph);

	void search(Vertex* source = nullptr);

protected:
	void printInfo();
};

#endif