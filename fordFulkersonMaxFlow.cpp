#include <boost/range/adaptor/map.hpp>
#include "fordFulkersonMaxFlow.h"

FordFulkersonMaxFlow::FordFulkersonMaxFlow(Graph* graph)
	: GraphAlgo(graph),
	  maxFlow(0),
	  capacity(boost::numeric::ublas::matrix<int>(graph->weightrix)),
	  flow(boost::numeric::ublas::matrix<int>(graph->weightrix.size1(), graph->weightrix.size2(), 0)),
	  parent(std::map<Vertex*, Vertex*>())
{
	for (int i = 0; i < (int)capacity.size1(); i++)
	{
		for (int j = 0; j < (int)capacity.size2(); j++)
		{
			if (capacity.at_element(i, j) == INT_MAX)
			{
				capacity.insert_element(i, j, 0);
			}
		}
	}
}

void FordFulkersonMaxFlow::search()
{
	using namespace std;

	Vertex *vert, *wert;

	while (breadthFirstSearch())
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

bool FordFulkersonMaxFlow::breadthFirstSearch()
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