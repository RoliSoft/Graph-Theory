#ifndef DIJKSTRA_SHORT_PATH_H
#define DIJKSTRA_SHORT_PATH_H

#include <unordered_map>
#include "graph.h"
#include "algo.h"
#include "edge.h"

class DijkstraShortPath : public GraphAlgo
{
public:
	std::unordered_map<Vertex*, int> distance;
	std::unordered_map<Vertex*, Vertex*> previous;
	Vertex* source;

	DijkstraShortPath(Graph* graph);

	void search(Vertex* source = nullptr);
	void dump();
};

#endif