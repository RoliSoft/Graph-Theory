#include <boost/range/adaptor/map.hpp>
#include "floydShortPath.h"

FloydShortPath::FloydShortPath(Graph* graph)
	: GraphAlgo(graph),
	  paths(boost::numeric::ublas::matrix<int>(graph->weightrix)),
	  nexts(boost::numeric::ublas::matrix<Vertex*>(graph->weightrix.size1(), graph->weightrix.size2(), nullptr))
{
}

void FloydShortPath::search()
{
	using namespace std;

	for (int k = 0; k < (int)paths.size1(); k++)
	{
		for (int i = 0; i < (int)paths.size1(); i++)
		{
			for (int j = 0; j < (int)paths.size1(); j++)
			{
				if ((paths.at_element(i, k) != INT_MAX && paths.at_element(k, j) != INT_MAX)
				 && (paths.at_element(i, j) > paths.at_element(i, k) + paths.at_element(k, j)))
				{
					paths.insert_element(i, j, paths.at_element(i, k) + paths.at_element(k, j));
					nexts.insert_element(i, j, graph->verts[k]);
				}
			}
		}
	}
}

void FloydShortPath::path(Vertex* src, Vertex* dst)
{
	using namespace std;

	cout << "  Shortest path from " << src->id << " to " << dst->id << ": " << endl;

	if (paths.at_element(src->id, dst->id) == INT_MAX)
	{
		cout << "   No path available." << endl << endl;
		return;
	}

	cout << "   " << src->id;

	int sum = 0;
	cout << _path(src, dst, sum) << " (" << sum << ")" << endl << endl;
}

std::string FloydShortPath::_path(Vertex* src, Vertex* dst, int& sum)
{
	auto next = nexts.at_element(src->id, dst->id);

	if (next == nullptr)
	{
		int weight = paths.at_element(src->id, dst->id);
		sum += weight;
		return " -[" + std::to_string(weight) + "]-> " + std::to_string(dst->id);
	}

	return _path(src, next, sum) + _path(next, dst, sum);
}

void FloydShortPath::dump()
{
	using namespace std;

	cout << " Floyd's algorithm:" << endl << "  Shortest path weights:" << endl;

	Graph::print(paths, INT_MAX, (*graph->verts.begin()).first);
}