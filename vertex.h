#ifndef VERTEX_H
#define VERTEX_H

#include <set>
#include "edge.h"

class Graph;

class Vertex
{
public:
	Graph* graph;
	int id;
	bool dir;
	std::set<Edge*, Edge::less> in, out, deg;

	Vertex(Graph* graph, int id);
};

#endif