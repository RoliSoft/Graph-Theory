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
	std::map<Vertex*, int> bmin;
	std::vector<Edge*> backEdges;
	std::unordered_set<Edge*> artEdges;
	std::unordered_set<Vertex*> artVerts;

	DepthFirstSearch(Graph* graph);

	void search();

private:
	void discover(Vertex* vert);

protected:
	void printInfo();
};

#endif