#include "graph.h"
#include "vertex.h"
#include "edge.h"
#include "edge_less.h"

Vertex::Vertex(Graph* graph, int id)
{
	this->graph = graph;
	this->id = id;

	if (graph->directed)
	{
		this->in  = std::set<Edge*, edge_less>();
		this->out = std::set<Edge*, edge_less>();
	}
	else
	{
		this->deg = std::set<Edge*, edge_less>();
	}
}