#include "graph.h"
#include "edge.h"
#include "vertex.h"

Edge::Edge(Vertex* src, Vertex* dst, int weight)
{
	this->src = src;
	this->dst = dst;
	this->weight = weight;

	if (src->graph->directed)
	{
		this->src->out.emplace(this);
		this->dst->in.emplace(this);
	}
	else
	{
		if (this->src->deg.find(this) == this->src->deg.end())
		{
			this->src->deg.emplace(this);
		}

		if (this->dst->deg.find(this) == this->dst->deg.end())
		{
			this->dst->deg.emplace(this);
		}
	}
}