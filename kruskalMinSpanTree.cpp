#include <unordered_set>
#include <deque>
#include "kruskalMinSpanTree.h"

KruskalMinSpanTree::KruskalMinSpanTree(Graph* graph)
	: GraphAlgo(graph),
	  tree(std::vector<Edge*>()),
	  weight(0)
{
}

void KruskalMinSpanTree::search()
{
	using namespace std;

	unordered_set<Vertex*> verts;
	unordered_set<Edge*> edges;
	deque<Edge*> edgeAsc(graph->edges.begin(), graph->edges.end());

	sort(edgeAsc.begin(), edgeAsc.end(), [](const Edge* a, const Edge* b){ return a->weight < b->weight; });
	
	while (edges.size() != graph->verts.size() - 1)
	{
		auto edge = edgeAsc.front();
		edgeAsc.pop_front();

		if (verts.find(edge->dst) != verts.end() && verts.find(edge->src) != verts.end() && edges.size() != graph->verts.size() - 2)
		{
			continue;
		}

		verts.emplace(edge->src);
		verts.emplace(edge->dst);

		edges.emplace(edge);
		tree.push_back(edge);

		weight += edge->weight;
	}

	printInfo();
}


void KruskalMinSpanTree::printInfo()
{
	using namespace std;

	cout << " Kruskal's algorithm:" << endl << "  Minimum spanning tree:" << endl << endl;

	for (auto edge : tree)
	{
		cout << "   " << edge->src->id << " <-[" << edge->weight << "]-> " << edge->dst->id << endl;
	}

	cout << endl << "  Total path weight: " << weight << endl << endl;
}