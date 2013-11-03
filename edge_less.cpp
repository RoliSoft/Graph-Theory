#include "edge_less.h"
#include "vertex.h"
#include "graph.h"

int _getHash(const Edge* e)
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

bool edge_less::operator()(const Edge* lhs, const Edge* rhs) const
{
	return _getHash(lhs) < _getHash(rhs);
}