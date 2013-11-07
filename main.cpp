#include <iostream>
#include "graph.h"
#include "depthFirstSearch.h"
#include "depthFirstSearchRev.h"
#include "breadthFirstSearch.h"
#include "primMinSpanTree.h"

int main()
{
	using namespace std;

	Graph graph("input.txt");
	//DepthFirstSearch dfs(&graph);
	//DepthFirstSearchRev dfr(&graph, &dfs);
	//BreadthFirstSearch bfs(&graph);
	PrimMinSpanTree pms(&graph);

	//dfs.search();
	//dfr.search();
	//bfs.search();
	pms.search();

	system("pause");
	return EXIT_SUCCESS;
}