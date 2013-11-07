#ifndef DEPTH_FIRST_SEARCH_H
#define DEPTH_FIRST_SEARCH_H

#include <unordered_set>
#include "graph.h"
#include "search.h"
#include "edge.h"

class DepthFirstSearch : public GraphSearch
{
public:
	int time;
	bool acyclic;
	std::map<Vertex*, int> tock;
	std::map<Vertex*, int> levels;
	std::vector<Edge*> backEdges;
	std::unordered_set<Edge*> artEdges;
	std::unordered_set<Vertex*> artVerts;

	DepthFirstSearch(Graph* graph);

	void search();

private:
	int discover(Vertex* vert, int level = 0);

protected:
	void printInfo();
};

#endif