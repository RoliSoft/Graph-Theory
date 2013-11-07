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
	bool directed; // ir�ny�tatotts�g
	bool weighted; // s�lyozotts�g
	std::map<int, Vertex*> verts; // cs�cslista [Ki_SzL, Be_SzL, KiBe_SzL]
	std::set<Edge*, Edge::less> edges; // �llista [ElL]
	Matrix<bool> matrix; // szomsz�ds�gi m�trix [SzM]
	Matrix<int> weightrix; // s�lyozott szomsz�ds�gi m�trix [SulyM]

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