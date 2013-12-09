#include <iostream>
#include "graph.h"
#include "depthFirstSearch.h"
#include "depthFirstSearchRev.h"
#include "breadthFirstSearch.h"
#include "primMinSpanTree.h"
#include "kruskalMinSpanTree.h"
#include "dijkstraShortPath.h"
#include "bellmanFordShortPath.h"
#include "viterbiShortPath.h"
#include "floydShortPath.h"
#include "autoShortPath.h"
#include "criticalPathMethod.h"

int main()
{
	using namespace std;

	Graph graph("input.txt");
	DepthFirstSearch dfs(&graph);
	DepthFirstSearchRev dfr(&graph, &dfs);
	BreadthFirstSearch bfs(&graph);
	PrimMinSpanTree pms(&graph);
	KruskalMinSpanTree kms(&graph);
	//DijkstraShortPath dsp(&graph);
	//BellmanFordShortPath bfp(&graph);
	//ViterbiShortPath vsp(&graph, &dfs);
	AutoShortPath asp(&graph, &dfs);
	FloydShortPath fsp(&graph);
	CriticalPathMethod cpm(&graph);

	dfs.search(); dfs.dump();
	dfr.search(); dfr.dump();
	bfs.search(); bfs.dump();
	pms.search(); pms.dump();
	kms.search(); kms.dump();
	//dsp.search(); dsp.dump();
	//bfp.search(); bfp.dump();
	//vsp.search(); vsp.dump();
	asp.search(); asp.dump();
	fsp.search(); fsp.dump(); fsp.path(graph.verts[4], graph.verts[1]);
	cpm.search(); cpm.dump();

	system("pause");
	return EXIT_SUCCESS;
}