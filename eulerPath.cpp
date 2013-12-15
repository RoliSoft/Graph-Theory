#include <boost/range/adaptor/map.hpp>
#include "eulerPath.h"

EulerPath::EulerPath(Graph* graph)
	: GraphAlgo(graph),
	  path(std::vector<Edge*>())
{
}

void EulerPath::search()
{
	std::vector<Edge*> visited;

	for (auto vert : graph->verts | boost::adaptors::map_values)
	{
		for (auto edge : vert->deg)
		{
			visited.push_back(edge);

			if (recurse(edge, visited))
			{
				break;
			}

			visited.clear();
		}
	}
}

void EulerPath::dump()
{
	using namespace std;

	cout << " Euler's " << name() << ":" << endl;

	if (path.size() == 0)
	{
		cout << "  No Eulerian " << name() << " available for the graph." << endl << endl;
		return;
	}

	for (auto edge : path)
	{
		cout << "  " << edge->src->id << " <-> " << edge->dst->id << endl;
	}

	cout << endl;
}

std::string EulerPath::name()
{
	return "path";
}

boost::tribool EulerPath::check(Edge* edge, std::vector<Edge*>& visited)
{
	if (visited.size() == graph->edges.size() - 1)
	{
		return true;
	}

	return boost::indeterminate;
}

bool EulerPath::recurse(Edge* edge, std::vector<Edge*> visited)
{
	boost::tribool cres;
	if (!boost::indeterminate(cres = check(edge, visited)))
	{
		if (cres)
		{
			path = visited;
		}

		return cres;
	}

	/*for (auto edge2 : edge->src->deg)
	{
		std::vector<Edge*> visitcpy(visited);

		if (std::find(visitcpy.begin(), visitcpy.end(), edge2) != visitcpy.end())
		{
			continue;
		}

		visitcpy.push_back(edge2);

		if (recurse(edge2, visitcpy))
		{
			return true;
		}
	}*/

	for (auto edge2 : edge->dst->deg)
	{
		std::vector<Edge*> visitcpy(visited);

		if (std::find(visitcpy.begin(), visitcpy.end(), edge2) != visitcpy.end())
		{
			continue;
		}

		visitcpy.push_back(edge2);

		if (recurse(edge2, visitcpy))
		{
			return true;
		}
	}

	return false;
}