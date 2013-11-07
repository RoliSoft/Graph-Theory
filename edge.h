#ifndef EDGE_H
#define EDGE_H

class Edge
{
public:
	class Vertex *src, *dst;
	int weight;

	Edge(class Vertex* src, class Vertex* dst, int weight = 0);

	~Edge();

	struct hash { // std::hash<Edge*>
		std::size_t operator()(const Edge* e) const;
	};

	struct equal { // std::equal_to<Edge*>
		bool operator()(const Edge* lhs, const Edge* rhs) const;
	};

	struct less { // std::less<Edge*>
		bool operator()(const Edge* lhs, const Edge* rhs) const;
	};
};

#endif