#include <iostream>
#include "graph.h"
#include "depthFirstSearch.h"
#include "depthFirstSearchRev.h"
#include "breadthFirstSearch.h"
#include "primMinSpanTree.h"
#include "kruskalMinSpanTree.h"
#include "dijkstraShortPath.h"
#include "bellmanFordShortPath.h"
#include "topoSortShortPath.h"

int main()
{
	using namespace std;

	Graph graph("input.txt");
	DepthFirstSearch dfs(&graph);
	DepthFirstSearchRev dfr(&graph, &dfs);
	BreadthFirstSearch bfs(&graph);
	PrimMinSpanTree pms(&graph);
	KruskalMinSpanTree kms(&graph);
	DijkstraShortPath dsp(&graph);
	BellmanFordShortPath bfp(&graph);
	TopoSortShortPath tsp(&graph, &dfs);

	dfs.search(); dfs.dump();
	dfr.search(); dfr.dump();
	bfs.search(); bfs.dump();
	pms.search(); pms.dump();
	kms.search(); kms.dump();
	dsp.search(); dsp.dump();
	bfp.search(); bfp.dump();
	tsp.search(); tsp.dump();

	system("pause");
	return EXIT_SUCCESS;
}