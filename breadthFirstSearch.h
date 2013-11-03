#ifndef BREADTH_FIRST_SEARCH_H
#define BREADTH_FIRST_SEARCH_H

#include "graph.h"
#include "search.h"

class BreadthFirstSearch : public GraphSearch
{
public:
	BreadthFirstSearch(Graph* graph);

	void search();
};

#endif