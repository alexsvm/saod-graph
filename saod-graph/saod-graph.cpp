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
	struct node {
		int node_idx;
		double node_weight;
		node(int idx, double weight = 0) : node_idx(idx), node_weight(weight) { };
		bool operator < (const node & second) { return node_idx < second.node_idx; };
		bool operator == (const node & second) { return node_idx == second.node_idx; };
	};

	struct verge {
		node* node_A;
		node* node_B;
		double verge_weight;
		verge(node* A, node* B, double weight) : node_A(A), node_B(B), verge_weight(weight) { };
		verge(int A, int B, double weight) : node_A(new node(A)), node_B(new node(B)), verge_weight(weight) { };
		bool operator < (const verge & second) { 
			return (node_A->node_idx < second.node_A->node_idx) 
				|| (node_A->node_idx == second.node_A->node_idx 
					&& node_B->node_idx < second.node_B->node_idx);
		};
		bool operator == (const verge & second) { 
			return node_A->node_idx == second.node_A->node_idx 
				&& node_B->node_idx == second.node_B->node_idx; 
		};
	};

	typedef list<verge> Verges;
	typedef list<node> Nodes;
	typedef std::map<int, std::map<int, double>> ConnMap;

private:
	Verges _verges;
	Nodes _nodes;
	ConnMap _conn_map;

	void _re_map() {
		_conn_map.clear();
		for (const auto &n_col : _nodes) 
			for (const auto &n_row : _nodes) {
				verge * v = Get_Verge(n_col.node_idx, n_row.node_idx);
				if (v == nullptr) 
					_conn_map[n_col.node_idx][n_row.node_idx] = 0;
				else
					_conn_map[n_col.node_idx][n_row.node_idx] = v->verge_weight;
				/*for (const auto &v : _verges)
					if (v.node_A->node_idx == n_col.node_idx && v.node_B->node_idx == n_row.node_idx)
						_conn_map[n_col.node_idx][n_row.node_idx] = v.verge_weight;
					else
						_conn_map[n_col.node_idx][n_row.node_idx] = 0;*/
			}
	};

public:
	Graph() {};
	Graph(Graph const &G) = delete; // Удаляем конструктор копирования
	Graph(Graph &&G) = delete; // Удаляем конструктор перемещения
	void *operator new(std::size_t) = delete; // Удаляем операторы new
	void *operator new[](std::size_t) = delete; //
	
	node * Get_Node(int idx) {
		Graph::Nodes::iterator iter = std::find(_nodes.begin(), _nodes.end(), node(idx));
		//if (iter != std::end(_nodes))
		//	return &(*iter);
		//else
		//	return nullptr;
		return (iter != std::end(_nodes)) ? &(*iter) : nullptr;
	};

	node * Get_Node(node &_node) {
		Graph::Nodes::iterator iter = std::find(_nodes.begin(), _nodes.end(), _node);
		//if (iter != std::end(_nodes))
		//	return &(*iter);
		//else
		//	return nullptr;
		return (iter != std::end(_nodes)) ? &(*iter) : nullptr;
	};

	bool Nodes_Add(node node) {
		if (Get_Node(node.node_idx) == nullptr) {
			_nodes.push_back(node);
			_nodes.sort();
			return true;
		} else 
			return false;
	};

	bool Nodes_Add(int idx) { return Nodes_Add(node(idx)); };

	bool Nodes_Del(int idx) {
		for (auto iter = _nodes.begin(); iter != _nodes.end(); iter++)
			if (iter->node_idx == idx) {
				_nodes.erase(iter);
				return true;
			}
		return false;
	};

	verge * Get_Verge(int A, int B) {
		for (auto iter = _verges.begin(); iter != _verges.end(); iter++)
			if (iter->node_A->node_idx == A && iter->node_B->node_idx == B)
				return &(*iter);
		return nullptr;
	};

	verge * Get_Verge(node &nodeA, node &nodeB) {
		for (auto iter = _verges.begin(); iter != _verges.end(); iter++)
			if (iter->node_A->node_idx == nodeA.node_idx && iter->node_B->node_idx == nodeB.node_idx)
				return &(*iter);
		return nullptr;
	};

	void Verges_Add(node *A, node *B, double weight) {
		node * nodeA = Get_Node(*A);
		node * nodeB = Get_Node(*B);
		if (nodeA == nullptr) 
			Nodes_Add(*A);
		if (nodeB == nullptr) 
			Nodes_Add(*B);
		verge new_verge(nodeA ? nodeA : A, nodeB ? nodeB : B, weight);
		if (Get_Verge(*new_verge.node_A, *new_verge.node_B) == nullptr) {
			_verges.push_back(new_verge);
			_verges.sort();
		}
	};

	void Verges_Add(int A, int B, double weight) { Verges_Add(new node(A), new node(B), weight); };

	bool Verges_Del(int A, int B);

	

	void Print_Verges() {
		for (const auto &it : _verges)
			cout << "(" << it.node_A->node_idx << ")-(" << it.node_B->node_idx << ")[" << it.verge_weight <<"]\t";
		cout << endl;
	}

	void Print_Nodes() {
		for (const auto &it : _nodes) 
			cout << it.node_idx << "(" << it.node_weight << ")\t";
		cout << endl;
	};

	void Print_Connectivity_Matrix() { // Выводим граф в виде матрицы смежности
		_re_map();
		cout << "[ ]\t";
		for (auto iter : _conn_map)
			cout << "[" << iter.first << "]\t";
		cout << endl;
		for (auto iter : _conn_map) {
			cout << "[" << iter.first << "]\t";
			for (auto iter2 : iter.second) {
				cout << iter2.second << "\t";
			}
			cout << endl;
		}
	}

};

int main()
{
	//Graph* ptr = new Graph;
	
	Graph::verge v1(1, 3, 10.0);
	Graph::verge v2(1, 2, 10.0);
	Graph::verge v3(2, 1, 10.0);
	Graph::verge v4(1, 1, 10.0);
	Graph::verge v5(1, 3, 20.0);

	cout << (v1 < v2) << endl;
	cout << (v1 == v2) << endl;
	cout << (v1 == v5) << endl;

	Graph g1;
	g1.Nodes_Add(1);
	g1.Nodes_Add(3);
	g1.Nodes_Add(5);
	g1.Nodes_Add(Graph::node(7, 10));
	cout << "Printing nodes: " << endl;
	g1.Print_Nodes();

	//std::shared_ptr<Graph::graph_node> node_ptr = g1.Get_Node(1);
	Graph::node * node = g1.Get_Node(1);
	if (node) 
		cout << "node found = " << node->node_idx << "(" << node->node_weight << ")" << endl;
	Graph::node node2(5, 10);
	g1.Get_Node(node2) ? 
		cout << "node already exist = " << node2.node_idx << "(" << node2.node_weight << ")" << endl :
		cout << "not found!";

	cout << endl << "Adding verges and print nodes and verges..." << endl;
	g1.Verges_Add(7, 8, 10.0);
	g1.Verges_Add(8, 9, 11.0);
	g1.Verges_Add(1, 8, 5.0);
	g1.Verges_Add(2, 9, 6.0); 
	g1.Verges_Add(2, 9, 666.0);
	g1.Verges_Add(2, 9, 666.0);
	g1.Verges_Add(node, &node2, 999.0);
	g1.Print_Nodes();
	g1.Print_Verges();
	cout << "\nPrinting connectivity matrix:" << endl;
	g1.Print_Connectivity_Matrix();

	cout << endl << "\n\nEnter x to exit...";
	char a;
	do { a = cin.get(); } while (a != 'x');

    return 0;
}

