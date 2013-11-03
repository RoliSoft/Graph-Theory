#ifndef DEPTH_FIRST_SEARCH_H
#define DEPTH_FIRST_SEARCH_H

#include "graph.h"
#include "search.h"

class DepthFirstSearch : public GraphSearch
{
public:
	int time;
	bool acyclic;
	std::map<Vertex*, int> tock;

	DepthFirstSearch(Graph* graph);

	void search();

private:
	void discover(Vertex* vert);

protected:
	void printInfo();
};

#endif