#include <iostream>
#include "graph.h"
#include "depthFirstSearch.h"
#include "breadthFirstSearch.h"

int main()
{
	using namespace std;

	Graph graph("input.txt");
	DepthFirstSearch dfs(&graph);
	BreadthFirstSearch bfs(&graph);

	dfs.search();
	dfs.searchRev();
	bfs.search();

	system("pause");
	return EXIT_SUCCESS;
}