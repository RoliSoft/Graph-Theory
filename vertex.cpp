#include "graph.h"
#include "vertex.h"
#include "edge.h"

Vertex::Vertex(Graph* graph, int id)
	: graph(graph),
	  id(id)
{
	if (graph->directed)
	{
		this->in  = std::set<Edge*, Edge::less>();
		this->out = std::set<Edge*, Edge::less>();
	}
	else
	{
		this->deg = std::set<Edge*, Edge::less>();
	}
}