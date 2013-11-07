#ifndef GRAPH_H
#define GRAPH_H

#include <map>
#include <vector>
#include <deque>
#include <string>
#include <tuple>
#include <set>
#include "vertex.h"
#include "edge.h"
#include "matrix.h"

class Graph
{
public:
	bool directed; // irányítatottság
	bool weighted; // súlyozottság
	std::map<int, Vertex*> verts; // csúcslista [Ki_SzL, Be_SzL, KiBe_SzL]
	std::set<Edge*, Edge::less> edges; // éllista [ElL]
	Matrix<bool> matrix; // szomszédsági mátrix [SzM]
	Matrix<int> weightrix; // súlyozott szomszédsági mátrix [SulyM]

	Graph(std::string file);
	Graph(bool directed, bool weighted, int vertCnt, std::vector<std::tuple<int, int, int>> edgeList);

	bool addEdge(Edge* edge);
	bool removeEdge(Edge* edge);

	Graph* getCloned();
	Graph* getTransposed();

private:
	void init(bool directed, bool weighted, int vertCnt, std::vector<std::tuple<int, int, int>> edgeList);
};

#endif