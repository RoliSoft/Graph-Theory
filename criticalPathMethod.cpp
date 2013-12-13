#include <boost/range/adaptor/map.hpp>
#include "criticalPathMethod.h"

CriticalPathMethod::CriticalPathMethod(Graph* graph)
	: GraphAlgo(graph),
	  path(std::vector<Vertex*>())
{
}

void CriticalPathMethod::search()
{
	using namespace std;

	length = getMaxForward((*graph->verts.begin()).second);

	for (auto vert : graph->verts | boost::adaptors::map_values)
	{
		if (getMaxForward(vert) + getMaxBackward(vert) == length)
		{
			path.push_back(vert);
		}
	}
}

void CriticalPathMethod::dump()
{
	using namespace std;

	cout << " Critical path method:" << endl << "  Length of the critical path: " << length << endl << endl << "  Critical vertices:" << endl << "   ";

	auto first = true;
	for (auto vert : path)
	{
		if (first)
		{
			first = false;
		}
		else
		{
			cout << " -> ";
		}

		cout << vert->id;
	}

	cout << endl << endl;
}

int CriticalPathMethod::getMaxForward(Vertex* vert)
{
	int max = 0;
	
	if (vert != (*graph->verts.rbegin()).second)
	{
		for (auto edge : vert->out)
		{
			int current = edge->weight + getMaxForward(edge->dst);

			if (current > max)
			{
				max = current;
			}
		}
	}

	return max;
}

int CriticalPathMethod::getMaxBackward(Vertex* vert)
{
	int max = 0;

	if (vert != (*graph->verts.begin()).second)
	{
		for (auto edge : vert->in)
		{
			int current = edge->weight + getMaxBackward(edge->src);

			if (current > max)
			{
				max = current;
			}
		}
	}

	return max;
}