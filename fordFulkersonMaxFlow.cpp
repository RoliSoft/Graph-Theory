#include <boost/range/adaptor/map.hpp>
#include "fordFulkersonMaxFlow.h"

FordFulkersonMaxFlow::FordFulkersonMaxFlow(Graph* graph)
	: GraphAlgo(graph),
	  maxFlow(0),
	  capacity(boost::numeric::ublas::matrix<int>(graph->weightrix)),
	  parent(std::map<Vertex*, Vertex*>())
{
}

void FordFulkersonMaxFlow::search()
{
	using namespace std;

	Vertex *vert, *wert;

	while (isFlowPossible())
	{
		int pathFlow = INT_MAX;

		for (wert = (*graph->verts.rbegin()).second; wert != (*graph->verts.begin()).second; wert = parent[wert])
		{
			vert = parent[wert];
			pathFlow = min(pathFlow, capacity.at_element(vert->id, wert->id));
		}

		for (wert = (*graph->verts.rbegin()).second; wert != (*graph->verts.begin()).second; wert = parent[wert])
		{
			vert = parent[wert];
			capacity.insert_element(vert->id, wert->id, capacity.at_element(vert->id, wert->id) - pathFlow);
			capacity.insert_element(wert->id, vert->id, capacity.at_element(wert->id, vert->id) + pathFlow);
		}

		maxFlow += pathFlow;
	}
}

void FordFulkersonMaxFlow::dump()
{
	using namespace std;

	cout << " Ford-Fulkerson's algorithm:" << endl << "  Maximum possible flow: " << maxFlow << endl << endl;
}

bool FordFulkersonMaxFlow::isFlowPossible()
{
	using namespace std;

	map<Vertex*, bool> visited;
	deque<Vertex*> queue { (*graph->verts.begin()).second };

	for (auto vert : graph->verts | boost::adaptors::map_values)
	{
		visited[vert] = false;
	}

	visited[queue.front()] = true;
	parent[queue.front()]  = nullptr;

	while (!queue.empty())
	{
		auto vert = queue.front();
		queue.pop_front();

		for (auto edge : vert->out)
		{
			auto wert = edge->dst;

			if (!visited[wert] && capacity.at_element(vert->id, wert->id) > 0)
			{
				queue.push_back(wert);

				parent[wert]  = vert;
				visited[wert] = true;
			}
		}
	}
	
	return visited[(*graph->verts.rbegin()).second];
}