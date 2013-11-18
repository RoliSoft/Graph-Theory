#ifndef DEPTH_FIRST_SEARCH_H
#define DEPTH_FIRST_SEARCH_H

#include <unordered_map>
#include <unordered_set>
#include "graph.h"
#include "search.h"
#include "edge.h"

class DepthFirstSearch : public GraphSearch
{
public:
	int time;
	bool acyclic, negWeight;
	std::unordered_map<Vertex*, int> tock;
	std::unordered_map<Vertex*, int> levels;
	std::unordered_set<Edge*> backEdges;
	std::unordered_set<Edge*> artEdges;
	std::unordered_set<Vertex*> artVerts;

	DepthFirstSearch(Graph* graph);

	void search();
	void dump();

private:
	int discover(Vertex* vert, int level = 0);
};

#endif