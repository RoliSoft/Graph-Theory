#ifndef GRAPH_H
#define GRAPH_H

#include <map>
#include <vector>
#include <deque>
#include <string>
#include <tuple>
#include "vertex.h"
#include "edge.h"
#include "matrix.h"

class Graph
{
public:
	bool directed; // irányítatottság
	bool weighted; // súlyozottság
	int vertCnt; // csúcsok száma
	int edgeCnt; // élek száma
	std::map<int, Vertex*> verts; // csúcslista [Ki_SzL, Be_SzL, KiBe_SzL]
	std::vector<Edge*> edges; // éllista [ElL]
	Matrix<bool> matrix; // szomszédsági mátrix [SzM]
	Matrix<int> weightrix; // súlyozott szomszédsági mátrix [SulyM]

	Graph(std::string file);
	Graph(bool directed, bool weighted, int vertCnt, int edgeCnt, std::vector<std::tuple<int, int, int>> edgeList);

	Graph* clone();
	Graph* transpose();
};

#endif