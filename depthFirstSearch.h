#ifndef DEPTH_FIRST_SEARCH_H
#define DEPTH_FIRST_SEARCH_H

#include <unordered_set>
#include "graph.h"
#include "search.h"
#include "edge.h"

class DepthFirstSearch : public GraphSearch
{
public:
	int time, timeRev;
	bool acyclic;
	std::map<Vertex*, int> tock;
	std::map<Vertex*, int> bmin;
	std::vector<Edge*> backEdges;
	std::unordered_set<Edge*> artEdges;
	std::unordered_set<Vertex*> artVerts;
	std::map<Vertex*, color> colorsRev;
	std::vector<Vertex*> grayedRev;
	std::vector<Vertex*> blackedRev;
	std::map<Edge*, kind> categsRev;
	std::map<Vertex*, int> tickRev;
	std::map<Vertex*, int> tockRev;

	DepthFirstSearch(Graph* graph);

	void search();
	void searchRev();

private:
	void discover(Vertex* vert);
	void discoverRev(Vertex* vert);

protected:
	void printInfo();
	void printInfoRev();
};

#endif