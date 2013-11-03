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
	bool directed; // ir�ny�tatotts�g
	bool weighted; // s�lyozotts�g
	int vertCnt; // cs�csok sz�ma
	int edgeCnt; // �lek sz�ma
	std::map<int, Vertex*> verts; // cs�cslista [Ki_SzL, Be_SzL, KiBe_SzL]
	std::vector<Edge*> edges; // �llista [ElL]
	Matrix<bool> matrix; // szomsz�ds�gi m�trix [SzM]
	Matrix<int> weightrix; // s�lyozott szomsz�ds�gi m�trix [SulyM]

	Graph(std::string file);
	Graph(bool directed, bool weighted, int vertCnt, int edgeCnt, std::vector<std::tuple<int, int, int>> edgeList);

	Graph* clone();
	Graph* transpose();
};

#endif