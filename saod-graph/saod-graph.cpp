// saod-graph.cpp: 
// Написать процедуру формирования ориентированного графа G, представив его в виде динамической структуры.
#include <memory>
#include <iostream>
#include <list>   
#include <algorithm>
#include <map>
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

	typedef list<graph_verge> Verges;
	typedef list<graph_node> Nodes;
	typedef std::map<int, std::map<int, double>> ConnMap;

private:
	Verges _verges;
	Nodes _nodes;
	ConnMap _conn_map;

	void _re_map() {
		_conn_map.clear();
		

	};

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

	bool Nodes_Add(graph_node node) {
		bool node_exist = false;
		for (auto iter = _nodes.begin(); iter != _nodes.end(); iter++)
			if (iter->node_idx == node.node_idx)
				node_exist = true;
		if (node_exist)
			return false;
		else {
			_nodes.push_back(node);
			return true;
		}
	};
	bool Nodes_Add(int idx) { return Nodes_Add(graph_node(idx)); };
	bool Nodes_Del(int idx) {
		for (auto iter = _nodes.begin(); iter != _nodes.end(); iter++)
			if (iter->node_idx == idx) {
				_nodes.erase(iter);
				return true;
			}
		return false;
	};

	graph_node * Get_Node(int idx) {
		Graph::Nodes::iterator iter = std::find(_nodes.begin(), _nodes.end(), graph_node(idx));
		if (iter != std::end(_nodes)) 
			return &(*iter);
		else 
			return nullptr;
	};

	void Print_Verges();
	void Print_Nodes() {
		for (const auto &it : _nodes) 
			cout << it.node_idx << "(" << it.node_weight << ")\t";
		cout << endl;
		//for (auto iter = _nodes.begin(); iter != _nodes.end(); iter++)
		//	cout << iter->node_idx << "(" << iter->node_weight << ")\t";
		//cout << endl;
	};
	void Print_Connectivity_Matrix(); // Выводим граф в виде матрицы смежности

};

int main()
{
	//Graph* ptr = new Graph;
	
	Graph::graph_verge v1(1, 3, 10.0);
	Graph::graph_verge v2(1, 2, 10.0);
	Graph::graph_verge v3(2, 1, 10.0);
	Graph::graph_verge v4(1, 1, 10.0);
	Graph::graph_verge v5(1, 3, 20.0);

	cout << (v1 < v2) << endl;
	cout << (v1 == v2) << endl;
	cout << (v1 == v5) << endl;


	Graph g1;
	g1.Nodes_Add(1);
	g1.Nodes_Add(3);
	g1.Nodes_Add(5);
	g1.Nodes_Add(Graph::graph_node(7, 10));
	cout << "Printing nodes: " << endl;
	g1.Print_Nodes();

	//std::shared_ptr<Graph::graph_node> node_ptr = g1.Get_Node(1);
	Graph::graph_node * node = g1.Get_Node(1);
	if (node) 
		cout << "node found = " << node->node_idx << "(" << node->node_weight << ")" << endl;

	cout << endl << "\n\nEnter x to exit...";
	char a;
	do { a = cin.get(); } while (a != 'x');

    return 0;
}

