#include "iostream"
#include "fstream"
#include "iomanip"
#include "deque"
#include "graph.h"

Graph::Graph(std::string file)
{
	using namespace std;

	ifstream fs(file);

	fs >> directed;
	fs >> weighted;
	fs >> vertices;
	fs >> edges;

	cout << " Number of vertices: " << vertices << "; edges: " << edges << "; graph is " << (!directed ? "not " : "") << "directed and " << (!weighted ? "not " : "") << "weighted." << endl << endl;

	verts  = map<int, Vertex*>();
	nums   = vector<Edge*>(edges);
	matrix = Matrix<bool>(vertices + 1, vertices + 1, false);

	if (weighted)
	{
		watrix = Matrix<int>(vertices + 1, vertices + 1, INT_MAX);
	}

	for (int i = 0; i < vertices; i++)
	{
		verts.emplace(i + 1, new Vertex(this, i + 1));
	}

	for (int i = 0; i < edges; i++)
	{
		int src, dst, weight = 0;

		fs >> src;
		fs >> dst;

		if (weighted)
		{
			fs >> weight;
		}

		nums[i] = new Edge(verts[src], verts[dst], weight);

		matrix.set(nums[i]->src->id, nums[i]->dst->id, true);

		if (weighted)
		{
			watrix.set(nums[i]->src->id, nums[i]->dst->id, weight);
		}

		cout << "  " << nums[i]->src->id << " " << (!directed ? "<" : "") << "-" << (weighted ? "[" + to_string(nums[i]->weight) + "]" : "") << "-> " << nums[i]->dst->id << endl;
	}

	cout << endl << " Edge list:" << endl;

	for (int i = 0; i < vertices; i++)
	{
		cout << endl << "  Vertex " << verts[i + 1]->id << ": " << endl;

		if (directed)
		{
			cout << "   <-  in: " << verts[i + 1]->in.size() << " [ ";

			for (auto ed : verts[i + 1]->in)
			{
				cout << ed->src->id << " ";
			}

			cout << "]" << endl << "   -> out: " << verts[i + 1]->out.size() << " [ ";

			for (auto ed : verts[i + 1]->out)
			{
				cout << ed->dst->id << " ";
			}

			cout << "]" << endl;
		}
		else
		{
			cout << "   degree: " << verts[i + 1]->deg.size() << " [ ";

			for (auto ed : verts[i + 1]->deg)
			{
				cout << (ed->dst == verts[i + 1] ? ed->src->id : ed->dst->id) << " ";
			}

			cout << "]" << endl;
		}
	}

	cout << endl << " Adjacency matrix:" << endl;
	matrix.print();

	if (weighted)
	{
		cout << " Weighted adjacency matrix:" << endl;
		watrix.print();
	}
}

enum color {
	white,
	gray,
	black
};

void _dfs(Vertex* vert, std::deque<Vertex*>* gray, std::deque<Vertex*>* black, std::map<int, color>* colors)
{
	(*colors)[vert->id] = color::gray;
	gray->emplace_back(vert);

	for (auto vert2 : vert->out)
	{
		if ((*colors)[vert2->dst->id] == color::white)
		{
			_dfs(vert2->dst, gray, black, colors);
		}
	}

	(*colors)[vert->id] = color::black;
	black->emplace_back(vert);
}

void Graph::depthFirstSearch()
{
	using namespace std;

	auto gray   = deque<Vertex*>();
	auto black  = deque<Vertex*>();
	auto colors = map<int, color>();

	for (int i = 0; i < vertices; i++)
	{
		colors[verts[i + 1]->id] = color::white;
	}

	for (auto vert : verts)
	{
		if (colors[vert.first] == color::white)
		{
			_dfs(vert.second, &gray, &black, &colors);

			gray.emplace_back(nullptr);
			black.emplace_back(nullptr);
		}
	}

	cout << " Depth-first search:" << endl << "  Gray:  ";

	auto sep = false;
	for (auto vert : gray)
	{
		if (vert == nullptr)
		{
			sep = true;
		}
		else
		{
			if (sep)
			{
				cout << "| ";
				sep = false;
			}

			cout << vert->id << " ";
		}
	}

	cout << endl << "  Black: ";

	sep = false;
	for (auto vert : black)
	{
		if (vert == nullptr)
		{
			sep = true;
		}
		else
		{
			if (sep)
			{
				cout << "| ";
				sep = false;
			}

			cout << vert->id << " ";
		}
	}

	cout << endl << endl;
}

void Graph::breathFirstSearch()
{
	using namespace std;

	cout << "Not yet implemented." << endl;
}

Graph::~Graph()
{
}