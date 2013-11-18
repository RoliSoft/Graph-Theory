#include "autoShortPath.h"
#include "depthFirstSearch.h"
#include "dijkstraShortPath.h"
#include "bellmanFordShortPath.h"
#include "topoSortShortPath.h"

AutoShortPath::AutoShortPath(Graph* graph, DepthFirstSearch* dfs)
	: GraphShortPath(graph),
	  dfs(dfs)
{
}

void AutoShortPath::search(Vertex* source)
{
	if (dfs == nullptr)
	{
		dfs = new DepthFirstSearch(graph);
	}

	if (dfs->blacked.size() == 0)
	{
		dfs->search();
	}

	if (dfs->acyclic)
	{
		algo = new TopoSortShortPath(graph, dfs);
	}
	else if (!dfs->negWeight)
	{
		algo = new DijkstraShortPath(graph);
	}
	else
	{
		algo = new BellmanFordShortPath(graph);
	}

	algo->search(source);
}

void AutoShortPath::dump()
{
	if (algo != nullptr)
	{
		algo->dump();
	}
}