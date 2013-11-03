#ifndef EDGE_H
#define EDGE_H

class Edge
{
public:
	class Vertex *src, *dst;
	int weight;

	Edge(class Vertex* src, class Vertex* dst, int weight = 0);
};

#endif