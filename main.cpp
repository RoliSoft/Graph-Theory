#include <iostream>
#include "graph.h"
#include "depthFirstSearch.h"
#include "depthFirstSearchRev.h"
#include "breadthFirstSearch.h"
#include "primMinSpanTree.h"
#include "kruskalMinSpanTree.h"
#include "dijkstraShortPath.h"
#include "bellmanFordShortPath.h"

int main()
{
	using namespace std;

	Graph graph("input.txt");
	//DepthFirstSearch dfs(&graph);
	//DepthFirstSearchRev dfr(&graph, &dfs);
	//BreadthFirstSearch bfs(&graph);
	PrimMinSpanTree pms(&graph);
	KruskalMinSpanTree kms(&graph);
	DijkstraShortPath dsp(&graph);
	BellmanFordShortPath bfp(&graph);

	//dfs.search();
	//dfr.search();
	//bfs.search();
	pms.search();
	kms.search();
	dsp.search();
	bfp.search();

	system("pause");
	return EXIT_SUCCESS;
}