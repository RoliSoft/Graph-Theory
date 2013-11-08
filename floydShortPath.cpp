#include <boost/range/adaptor/map.hpp>
#include "floydShortPath.h"

FloydShortPath::FloydShortPath(Graph* graph)
	: GraphAlgo(graph),
	  paths(boost::numeric::ublas::matrix<int>(graph->weightrix))
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
				}
			}
		}
	}
}

void FloydShortPath::dump()
{
	using namespace std;

	cout << " Floyd's algorithm:" << endl << "  Shortest path weights:" << endl;

	Graph::print(paths, INT_MAX, (*graph->verts.begin()).first);
}