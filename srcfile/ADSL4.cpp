//============================================================================
// Name        : ADSL4.cpp
// Author      : kushal
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include <vector>
#include <string>
#include <stdlib.h>
using namespace std;

string Upper(string n)
{
	for(unsigned int i=0;i<n.size();i++)
	{
		if(n[i]>=97 && n[i]<=122)
		{
			n[i] = n[i] - 32;
		}
	}
	return n;
}
class Edge //Edges represent connection between two nodes,a flight pat so to say
{
protected :
	string n_name;
	int cost;
public:
	Edge()
	{
		n_name = "NULL";
		cost =0;
	}
	void display();
	friend class Node;
	friend class Graph;
};

class Node : public Edge
{

	vector <Edge > edge_list_in;
	vector <Edge > edge_list_out;
	string name;
public:
	Node()
	{
		name = "NULL";
	}
	void add_edge(Node* ,Node* ,int );
	void remove_edge(Node* ,Node* );
	Edge* find_edge(string );
	void display_info(Node *,Node *);
	friend class Graph;
};

class Graph : public Node
{
	vector <Node > node_list;
public:
	Node* find(string );
	void add_node(string );
	void remove_node(string );
	void display_out(Node* );
	void display_in(Node* );
	void display_all();
};

void Edge :: display()
{

	if(n_name.size()<7)
	{
		cout<<n_name<<"\t\t\t|"<<cost;
	}
	else
	{
		cout<<n_name<<"\t\t|"<<cost;
	}
	cout<<"\n";
}
Node* Graph:: find(string name)
{
	Node* n = new Node();
	n->name = "NULL";
	for(unsigned int i=0;i<node_list.size();i++)
	{
		if(node_list[i].name == name)
		{
			n = &node_list[i];
		}
	}
	return n;
}

Edge* Node :: find_edge(string name)
{
	Edge *e = new Edge;
	for(unsigned int i=0;i<edge_list_out.size();i++)
	{
		if(edge_list_out[i].n_name == name)
		{
			e = &edge_list_out[i];
			return e;
		}
	}
	return e;
}

void Node :: display_info(Node* n,Node* p)
{
	if(n->name == "NULL" || p->name == "NULL")
	{
		cout<<"No FLight paths between specified cities!\n";
	}
	Edge *e = n->find_edge(p->name);
	if(e->n_name != "NULL")
	{
		cout<<"A flight from "<<n->name<<" to "<<p->name<<"\nCost of flight is Rs."<<e->cost<<"\n";
	}
	else
	{
		cout<<"No flight path from "<<n->name<<" to "<<p->name<<"\n";
	}
	e = p->find_edge(n->name);
	if(e->n_name != "NULL")
	{
		cout<<"A flight from "<<p->name<<" to "<<n->name<<"\nCost of flight is Rs."<<e->cost<<"\n";
	}
	else
	{
		cout<<"No flight path from "<<p->name<<" to "<<n->name<<"\n";
	}
}
void Node :: add_edge(Node* begin,Node* end,int cost)
{
	if(begin->name == "NULL" )
	{
		cout<<"Specified departure city is not currently part of the network!\n";
		return;
	}
	if(end->name == "NULL")
	{
		cout<<"Specified arrival city is not currently part of the network!\n";
		return;
	}
	for(unsigned int i=0;i<begin->edge_list_out.size();i++)
	{
		if(begin->edge_list_out[i].n_name == end->name)
		{
			cout<<"A flightpath already exists between the specified cities!\nDo you Wish to over write it?[y/n]";
			char choice;
			cin>>choice;
			if(choice == 'n')
			{
				return;
			}
			else
			{
				Edge *e = new Edge;
				e = begin->find_edge(end->name);
				e->cost = cost;
				return;
			}
		}
	}
	Edge e;
	e.n_name = end->name;
	e.cost = cost;
	begin->edge_list_out.push_back(e);
	e.n_name = begin->name;
	end->edge_list_in.push_back(e);
}

void Node :: remove_edge(Node* b,Node* e)
{
	if(b->name == "NULL" )
	{
		cout<<"Specified departure city is not currently part of the network!\n";
		return;
	}
	if(e->name == "NULL")
	{
		cout<<"Specified arrival city is not currently part of the network!\n";
		return;
	}
	for(unsigned int i=0;i<b->edge_list_out.size();i++)
	{
		if(b->edge_list_out[i].n_name == e->name)
		{
			b->edge_list_out.erase(b->edge_list_out.begin()+i);
			continue;
		}
	}
	for(unsigned int i=0;i<e->edge_list_in.size();i++)
	{
		if(e->edge_list_in[i].n_name == b->name)
		{
			e->edge_list_in.erase(e->edge_list_in.begin()+i);
			continue;
		}
	}
}

void Graph :: add_node(string name)
{
	Node *n,p;
	n = find(name);
	if(n->name == "NULL")
	{
		n->name = name;
		p = *n;
		node_list.push_back(p);
	}
	else
	{
		cout<<"The specified City is already part of our network!\n";
	}
}

void Graph :: remove_node(string name)
{
	Node * p = new Node;
	p = find(name);
	if(p->name == "NULL")
	{
		cout<<"The city you have specified is not part of the network!\n";
	}
	else
	{
		unsigned int j= p->edge_list_out.size();
		for(unsigned int i=0;i<j;i++)
		{
			Node *q = new Node;
			q = find(p->edge_list_out[0].n_name);
			remove_edge(p,q);
		}
		j= p->edge_list_in.size();
		for(unsigned int i=0;i<j;i++)
		{
			Node *q = new Node;
			q = find(p->edge_list_in[0].n_name);
			remove_edge(q,p);
		}
		for(unsigned int i=0;i<node_list.size();i++)
		{
			if(p->name == node_list[i].name)
			{
				node_list.erase(node_list.begin()+i);
				return;
			}
		}
	}
}

void Graph::display_out(Node *p)
{
	if(p->name == "NULL")
	{
		cout<<"Specified Airport not present in current network!\n";
		return;
	}
	cout<<"Destination\t|Cost\t\n";
	cout<<"-------------------------------------------\n";
	for(unsigned int i=0;i<p->edge_list_out.size();i++)
	{
		p->edge_list_out[i].display();
	}
	cout<<"\n\n";
}

void Graph ::display_in(Node *p)
{
	if(p->name == "NULL")
	{
		cout<<"Specified Airport not present in current network!\n";
		return;
	}
	cout<<"Source\t\t|Cost\t\n";
	cout<<"-------------------------------------------\n";
	for(unsigned int i=0;i<p->edge_list_in.size();i++)
	{
		p->edge_list_in[i].display();
	}
	cout<<"\n\n";
}

void Graph :: display_all()
{
	cout<<"Source\t\t|Destination\t\t|Cost\t\n";
	cout<<"-----------------------------------------------------\n";
	for(unsigned int i=0;i<node_list.size();i++)
	{
		if(node_list[i].name.size()<9)
		{
			cout<<node_list[i].name<<"\t\t|";
		}
		else
		{

			cout<<node_list[i].name<<"\t|";
		}
		for(unsigned int j=0;j<node_list[i].edge_list_out.size();j++)
		{
			node_list[i].edge_list_out[j].display();
			if(j+1<node_list[i].edge_list_out.size())
			{
				cout<<"\t\t|";
			}
		}
		cout<<"\n-----------------------------------------------------\n";
		cout<<"\n";
	}
}
int main()
{
	Graph g;
	Node *n,*p;
	int cost = 0;
	char choice;
	string begin,end;
	do
	{
		cout<<"1.Add a City\n2.Remove a City\n3.Add a flight\n4.Remove a flight\n5.Display flight info for\n6.Display all outgoing flights from :\n7.Display all incoming flights to :\n8.Display all flights\n9.Exit\n";
		cin>>choice;
		switch(choice)
		{
		case '1':
			cout<<"Enter name of Airport : \n";
			cin.ignore();
			getline(cin, begin);
			begin = Upper(begin);
			g.add_node(begin);
			break;
		case '2':
			cout<<"Enter name of Airport : \n";
			cin.ignore();
			getline(cin, end);
			end = Upper(end);
			n = g.find(end);
			g.remove_node(end);
			break;
		case '3':
			cout<<"Enter City of Departure :\n";
			cin.ignore();
			getline(cin,begin);
			begin = Upper(begin);
			n = g.find(begin);
			cout<<"Enter city of arrival :\n";
			getline(cin,end);
			end = Upper(end);
			p = g.find(end);
			cout<<"Enter cost of flight:\n";
			try
			{
				do
				{
					cin>>cost;
					if(cin.good())
					{
						g.add_edge(n,p,cost);
					}
					else
					{
						cout<<"Please enter a valid Cost!\n";
						cin.clear();
						cin.ignore();
					}
				}while(!cin.good());
			}
			catch(int a)
			{
				cout<<"Please Enter valid value for Cost!\n";
			}
			break;
		case '4':
			cout<<"Enter City of Departure :\n";
			cin.ignore();
			getline(cin,begin);
			begin = Upper(begin);
			n = g.find(begin);
			cout<<"Enter city of arrival :\n";
			getline(cin,end);
			end = Upper(end);
			p = g.find(end);
			g.remove_edge(n,p);
			break;
		case '5':
			cout<<"(Enter Names of cities)\n";
			cin.ignore();
			getline(cin,begin);
			begin = Upper(begin);
			getline(cin,end);
			end = Upper(end);
			n = g.find(begin);
			p = g.find(end);
			g.display_info(n,p);
			break;
		case '6':
			cout<<"(Enter Name of the city)\n";
			cin.ignore();
			getline(cin,begin);
			begin = Upper(begin);
			n = g.find(begin);
			g.display_out(n);
			break;
		case '7':
			cout<<"(Enter Name of the city)\n";
			cin.ignore();
			getline(cin,begin);
			begin = Upper(begin);
			n = g.find(begin);
			g.display_in(n);
			break;
		case '8':
			g.display_all();
			break;
		case '9':
			exit(1);
			break;
		default:
			cout<<"Please enter valid option!\nTry Again!\n";
		}
	}while(true);
}
