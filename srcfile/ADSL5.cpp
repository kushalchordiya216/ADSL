//============================================================================
// Name        : ADSL5.cpp
// Author      : KUSHAL
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style ,You have a business with several
//offices; you want to lease phone lines to
//connect them up with each other; and the phone company charges different
//amounts of money to connect different pairs of cities. You want
//a set of lines that connects all your offices with a minimum total cost.
//Solve the problem by suggesting appropriate data structures. (solve using
//prims Or kruskal both)
//============================================================================

#include <iostream>
#include <string>
#include <vector>
#include <stdlib.h>
using namespace std;

class Node
{
	string name;
	bool marker;
	vector<Node *> node_list;
	vector<int> cost_list;

  public:
	Node()
	{
		name = "NULL";
		marker = false;
	}
	Node *check_list_in(string name)
	{
		for (unsigned int i = 0; i < node_list.size(); i++)
		{
			if (node_list[i]->name == name)
			{
				return node_list[i];
			}
		}
	}
	friend class Graph;
};

class Edge
{
  public:
	Node *begin;
	Node *end;
	int cost, index1, index2;
	Edge()
	{
		begin = NULL;
		end = NULL;
		cost = 0;
		index1 = 0;
		index2 = 0;
	}
};

class Graph : public Node
{
	vector<Node *> node_list;

  public:
	void reset_markers()
	{
		for (unsigned int i = 0; i < node_list.size(); i++)
		{
			node_list[i]->marker = false;
		}
	}
	void add_node();
	void add_edge(Node *);
	void remove_edge(Node *, Node *);
	void remove_node();
	void display();
	int nearest_neighbour(Node *p)
	{
		int cost = 9999, index = -1;
		for (unsigned int i = 0; i < p->node_list.size(); i++)
		{
			if (p->cost_list[i] < cost && p->node_list[i]->marker == false)
			{
				index = i;
				cost = p->cost_list[i];
			}
		}
		return index;
	}
	bool check_circuit(Node *begin, Node *end)
	{
		for (unsigned int i = 0; i < begin->node_list.size(); i++)
		{
			bool isCircuit;
			if (begin->node_list[i] == end)
			{
				return 1;
			}
			else if (begin->node_list[i]->marker == false)
			{
				begin->marker = true;
				isCircuit = check_circuit(begin->node_list[i], end);
				if (isCircuit == 1)
				{
					return 1;
				}
			}
		}
		return 0;
	}
	Edge *smallest_edge(int *, int);
	void kruskal();
	void prim(Node *);
	Node *check_list(string name)
	{
		for (unsigned int i = 0; i < node_list.size(); i++)
		{
			if (node_list[i]->name == name)
			{
				return node_list[i];
			}
		}
	}
	int find_index(string name)
	{
		for (unsigned int i = 0; i < node_list.size(); i++)
		{
			if (node_list[i]->name == name)
			{
				return i;
			}
		}
		return -1;
	}
	void change(int *arr, int m);
};

void Graph::change(int *arr, int m)
{
	{
		int i, j;
		for (i = 0; i < m; i++)
		{
			for (j = 0; j < m; j++)
			{
				*((arr + i * m) + j) = 0;
			}
		}
	}
}
Edge *Graph ::smallest_edge(int *matrix, int n)
{
	int cost = 9999;
	Edge *e = new Edge;
	for (unsigned int i = 0; i < node_list.size(); i++)
	{
		for (unsigned int j = 0; j < node_list[i]->node_list.size(); j++)
		{
			if (node_list[i]->cost_list[j] < cost) //&& *((matrix+i*n) + j) == 0)
			{
				int k = find_index(node_list[i]->node_list[j]->name);
				if (*((matrix + i * n) + k) == 0)
				{
					e->begin = node_list[i];
					e->end = node_list[i]->node_list[j];
					e->cost = node_list[i]->cost_list[j];
					e->index1 = i;
					e->index2 = k;
					cost = e->cost;
				}
			}
		}
	}
	return e;
}

void Graph::add_node()
{
	string name;
	cout << "Enter name of location:\n";
	cin.ignore();
	getline(cin, name);
	Node *p = check_list(name);
	if (p == NULL)
	{
		Node *q = new Node;
		q->name = name;
		node_list.push_back(q);
	}
	else if (p->name == name)
	{
		cout << "This location is already included!\n";
	}
}

void Graph::add_edge(Node *n)
{
	string name;
	cout << "Enter Name of the second location:\n";
	getline(cin, name);
	Node *p = this->check_list(name);
	if (p == NULL)
	{
		cout << "Given location is not currently included in the network!\n";
	}
	else
	{
		Node *q = n->check_list_in(p->name);
		if (q == NULL)
		{
			int cost;
			cout << "Enter cost:\n";
			cin >> cost;
			n->node_list.push_back(p);
			n->cost_list.push_back(cost);
			p->node_list.push_back(n);
			p->cost_list.push_back(cost);
		}
		else
		{
			cout << "Requested connection already exists!\n";
		}
	}
}

void Graph ::remove_edge(Node *n, Node *p)
{
	p = n->check_list_in(p->name);
	if (p == NULL)
	{
		return;
	}
	else
	{
		for (unsigned int i = 0; i < n->node_list.size(); i++)
		{
			if (n->node_list[i] == p)
			{
				n->node_list.erase(n->node_list.begin() + i);
				n->cost_list.erase(n->cost_list.begin() + i);
				for (unsigned int j = 0; j < p->node_list.size(); j++)
				{
					if (p->node_list[j] == n)
					{
						p->node_list.erase(p->node_list.begin() + j);
						p->cost_list.erase(p->cost_list.begin() + j);
					}
				}
			}
		}
	}
}

void Graph::remove_node()
{
	cout << "Enter name of location!\n";
	string name;
	cin.ignore();
	getline(cin, name);
	Node *p = check_list(name);
	for (unsigned int i = 0; i < node_list.size(); i++)
	{
		remove_edge(node_list[i], p);
	}
	for (unsigned int i = 0; i < node_list.size(); i++)
	{
		if (node_list[i] == p)
		{
			node_list.erase(node_list.begin() + i);
		}
	}
}

void Graph::display()
{
	cout << "Location\t|Connection\t|Cost\t\t|\n";
	cout << "--------------------------------------------------\n";
	for (unsigned int i = 0; i < node_list.size(); i++)
	{
		cout << node_list[i]->name;
		for (unsigned int j = 0; j < node_list[i]->node_list.size(); j++)
		{
			cout << "\t\t|";
			cout << node_list[i]->node_list[j]->name;
			cout << "\t\t|";
			cout << node_list[i]->cost_list[j] << "\t\t|";
			cout << "\n";
		}
		cout << "\n------------------------------------------------------\n";
	}
}

void Graph::prim(Node *begin)
{
	vector<Node *> path;
	vector<int> final_cost;
	unsigned int count;
	begin->marker = true;
	path.push_back(begin);
	count = 1;
	while (count < node_list.size())
	{
		int index, list_index;
		int min = 9999;
		Node *p = node_list[0];
		for (unsigned int i = 0; i < path.size(); i++)
		{
			index = nearest_neighbour(path[i]);
			if (index != -1)
			{
				if (min > path[i]->cost_list[index])
				{
					p = path[i];
					list_index = index;
					min = path[i]->cost_list[index];
				}
			}
		}
		p->node_list[list_index]->marker = true;
		path.push_back(p->node_list[list_index]);
		final_cost.push_back(p->cost_list[list_index]);
		count++;
	}
	cout << "Smallest spanning tree consists of:\n";
	cout << path[0]->name << "\n";
	path[0]->marker = false;
	for (unsigned int i = 0; i < path.size() - 1; i++)
	{
		cout << path[i + 1]->name << "\t" << final_cost[i] << "\n";
	}
	reset_markers();
}

void Graph::kruskal()
{
	//make a new graph for which smallest edge will be executed
	Graph g1;
	cout << "The Edges using kruskal's are:-\n";
	int matrix[node_list.size()][node_list.size()];
	change((int *)matrix, node_list.size());
	vector<Edge *> edge_list;
	unsigned int count = 0;
	while (count < node_list.size() - 1)
	{
		Edge *e = new Edge;
		bool pmarker = 0, qmarker = 0;
		e = smallest_edge((int *)matrix, node_list.size());
		matrix[e->index1][e->index2] = 1;
		matrix[e->index2][e->index1] = 1;
		Node *p = g1.check_list(e->begin->name);
		if (p == NULL)
		{
			p = new Node;
			p->name = e->begin->name;
			pmarker = 1;
		}
		Node *q = g1.check_list(e->end->name);
		if (q == NULL)
		{
			q = new Node;
			q->name = e->end->name;
			qmarker = 1;
		}
		if (!g1.check_circuit(p, q))
		{
			if (pmarker == 1)
			{
				g1.node_list.push_back(p);
			}
			if (qmarker == 1)
			{
				g1.node_list.push_back(q);
			}
			p->node_list.push_back(q);
			q->node_list.push_back(p);
			edge_list.push_back(e);
			count++;
		}
		g1.reset_markers();
	};
	for (unsigned int i = 0; i < edge_list.size(); i++)
	{
		cout << edge_list[i]->begin->name << "\t" << edge_list[i]->end->name << "\t" << edge_list[i]->cost << "\n";
	}
}

int main()
{
	Graph g;
	Node *p, *n;
	int i;
	char choice;
	string name;

	while (true)
	{
		cout << "1.Add a location\n2.Add a connection\n3.Remove a Connection\n4.Remove a location\n5.Display"
				"\n6.Prim's\n7.Kruskal's\n8.Nearest Neighbor:\n9.Exit\n";
		cin >> choice;
		switch (choice)
		{
		case '1':
			g.add_node();
			break;
		case '2':
			cin.ignore();
			getline(cin, name);
			p = g.check_list(name);
			if (p == NULL)
			{
				cout << "no\n";
			}
			else
			{
				g.add_edge(p);
			}
			break;
		case '3':
			cin.ignore();
			getline(cin, name);
			n = g.check_list(name);
			if (p == NULL)
			{
				cout << "no\n";
			}
			else
			{
				getline(cin, name);
				p = g.check_list(name);
				g.remove_edge(n, p);
			}
			break;
		case '4':
			g.remove_node();
			break;
		case '5':
			g.display();
			break;
		case '6':
			cout << "Enter starting Location:\n";
			cin.ignore();
			getline(cin, name);
			p = g.check_list(name);
			if (p == NULL)
			{
				cout << "No\n";
			}
			else
			{
				g.prim(p);
			}
			break;
		case '7':
			g.kruskal();
			break;
		case '8':
			cout << "Enter Name of location:\n";
			cin.ignore();
			getline(cin, name);
			p = g.check_list(name);
			i = g.nearest_neighbour(p);
			cout << " connection  no. " << i + 1 << " is nearest!\n";
			break;
		case '9':
			exit(1);
			break;
		default:
			cout << "Enter valid choice!\n";
		}
	};
}
