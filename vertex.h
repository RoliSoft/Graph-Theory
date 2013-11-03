#ifndef VERTEX_H
#define VERTEX_H

#include "set"
#include "edge_less.h"

class Vertex
{
public:
	class Graph* graph;
	int id;
	bool dir;
	std::set<Edge*, edge_less> in, out, deg;

	Vertex(class Graph* graph, int id);
};

#endif