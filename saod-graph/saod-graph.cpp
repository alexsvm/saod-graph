// saod-graph.cpp: 
// Написать процедуру формирования ориентированного графа G, представив его в виде динамической структуры.
#include <memory>
#include <iostream>
#include <list>     
#include <iterator> 

using namespace std;

class Graph {

public:
	struct graph_verge {
		graph_verge(int A, int B, double weight) : node_A(A), node_B(B), verge_weight(weight) { };
		int node_A;
		int node_B;
		double verge_weight;
		bool operator < (const graph_verge & second) { return (node_A < second.node_A) || (node_A == second.node_A && node_B < second.node_B); };
		bool operator == (const graph_verge & second) { return node_A == second.node_A && node_B == second.node_B; };
	};

	struct graph_node {
		graph_node(int idx, double weight = 0) : node_idx(idx), node_weight(weight) { };
		int node_idx;
		double node_weight;
		bool operator < (const graph_node & second) { return node_idx < second.node_idx; };
		bool operator == (const graph_node & second) { return node_idx == second.node_idx; };
	};

private:
	list<graph_verge> _verges;
	list<graph_node> _nodes;

public:
	Graph() {};
	Graph(Graph const &G) = delete; // Удаляем конструктор копирования
	Graph(Graph &&G) = delete; // Удаляем конструктор перемещения
	void *operator new(std::size_t) = delete; // Удаляем оператор new
	void *operator new[](std::size_t) = delete; //
	
	void Verges_Add(graph_node A, graph_node B, double weight);
	void Verges_Add(int A, int B, double weight) { Verges_Add(graph_node(A), graph_node(B), weight); };
	bool Verges_Del(int A, int B);
	std::shared_ptr<graph_verge> Get_Verge(int A, int B);

	void Nodes_Add(graph_node node);
	void Nodes_Add(int idx) { Nodes_Add(graph_node(idx)); };
	bool Nodes_Del(int idx);
	std::shared_ptr<graph_node> Get_Node(int idx);

	void Print_Verges();
	void Print_Nodes();
	void Print_Connectivity_Matrix();

};

int main()
{
	//Graph* ptr = new Graph;

	Graph g1;
	
	Graph::graph_verge v1(1, 3, 10.0);
	Graph::graph_verge v2(1, 2, 10.0);
	Graph::graph_verge v3(2, 1, 10.0);
	Graph::graph_verge v4(1, 1, 10.0);
	Graph::graph_verge v5(1, 3, 20.0);

	cout << (v1 < v2) << endl;
	cout << (v1 == v2) << endl;
	cout << (v1 == v5) << endl;

	cout << endl << "\n\nEnter x to exit...";
	char a;
	do { a = cin.get(); } while (a != 'x');

    return 0;
}

