#ifndef SEARCH_H
#define SEARCH_H

#include <deque>
#include <map>
#include <vector>
#include "graph.h"
#include "algo.h"
#include "vertex.h"

class GraphSearch : public GraphAlgo
{
public:
	enum color {
		_undefc,
		white,
		gray,
		black
	};

	enum kind {
		_undefk,
		tree,
		back,
		cross,
		forward
	};

	std::map<Vertex*, color> colors;
	std::vector<Vertex*> grayed;
	std::vector<Vertex*> blacked;
	std::map<Edge*, kind> categs;
	std::map<Vertex*, Vertex*> parents;
	std::map<Vertex*, int> tick;
	std::string parentheses;

	GraphSearch(Graph* graph);

protected:
	virtual void dump();
};

#endif