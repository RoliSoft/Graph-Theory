#ifndef DEPTH_FIRST_SEARCH_H
#define DEPTH_FIRST_SEARCH_H

#include "graph.h"
#include "search.h"
#include "edge.h"

class DepthFirstSearch : public GraphSearch
{
public:
	int time;
	bool acyclic;
	std::map<Vertex*, int> tock;
	std::vector<Edge*> backEdges;

	DepthFirstSearch(Graph* graph);

	void search();

private:
	void discover(Vertex* vert);
	void discoverRev(Vertex* vert);

protected:
	void printInfo();
};

#endif