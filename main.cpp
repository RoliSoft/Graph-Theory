#include <iostream>
#include "graph.h"
#include "depthFirstSearch.h"
#include "breadthFirstSearch.h"
#include "topologicalSort.h"

int main()
{
	using namespace std;

	auto graph = Graph("input.txt");
	auto dfs = DepthFirstSearch(&graph);
	auto bfs = BreadthFirstSearch(&graph);
	auto ts  = TopologicalSort(&graph, &dfs);

	dfs.search();
	bfs.search();
	//ts.sort();

	system("pause");
	return EXIT_SUCCESS;
}