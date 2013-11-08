#ifndef GRAPH_H
#define GRAPH_H

#include <map>
#include <vector>
#include <deque>
#include <string>
#include <tuple>
#include <set>
#include <boost/numeric/ublas/matrix.hpp>
#include "vertex.h"
#include "edge.h"

class Graph
{
public:
	bool directed; // ir�ny�tatotts�g
	bool weighted; // s�lyozotts�g
	std::map<int, Vertex*> verts; // cs�cslista [Ki_SzL, Be_SzL, KiBe_SzL]
	std::set<Edge*, Edge::less> edges; // �llista [ElL]
	boost::numeric::ublas::matrix<bool> matrix; // szomsz�ds�gi m�trix [SzM]
	boost::numeric::ublas::matrix<int> weightrix; // s�lyozott szomsz�ds�gi m�trix [SulyM]

	Graph(std::string file);
	Graph(bool directed, bool weighted, int vertCnt, const std::vector<std::tuple<int, int, int>>& edgeList);

	bool addEdge(Edge* edge);
	bool removeEdge(Edge* edge);

	Graph* getCloned();
	Graph* getTransposed();

	template <typename T> static void print(boost::numeric::ublas::matrix<T>& matrix, T def, int start = 0);

private:
	void init(bool directed, bool weighted, int vertCnt, const std::vector<std::tuple<int, int, int>>& edgeList);
};

#endif