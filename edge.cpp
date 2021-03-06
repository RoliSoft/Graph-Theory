#include "graph.h"
#include "edge.h"
#include "vertex.h"

Edge::Edge(Vertex* src, Vertex* dst, int weight)
	: src(src),
	  dst(dst),
	  weight(weight)
{
}

std::size_t Edge::hash::operator()(const Edge* e) const
{
	if (e->src->graph->directed)
	{
		return e->dst->id * 1000 + e->src->id;
	}
	else if (e->dst->id < e->src->id)
	{
		return e->dst->id * 1000 + e->src->id;
	}
	else
	{
		return e->src->id * 1000 + e->dst->id;
	}
}

bool Edge::equal::operator()(const Edge* lhs, const Edge* rhs) const
{
	return (lhs->dst == rhs->dst && lhs->src == rhs->src)
		|| (!lhs->src->graph->directed && lhs->src == rhs->dst && lhs->dst == rhs->src);
}

bool Edge::less::operator()(const Edge* lhs, const Edge* rhs) const
{
	Edge::hash hash;
	return hash(lhs) < hash(rhs);
}