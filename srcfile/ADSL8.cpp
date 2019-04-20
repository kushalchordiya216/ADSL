//============================================================================
// Name        : ADSL8.cpp
// Author      : kushal
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include <stdlib.h>
#include <queue>
using namespace std;

int compare(const string &x, const string &y)
{
	int minsize = min(x.size(), y.size());
	for (int i = 0; i < minsize; i++)
	{
		if (x[i] < y[i])
		{
			return 1;
		}
		else if (x[i] > y[i])
		{
			return -1;
		}
	}
	if (x.size() > y.size())
	{
		return -1;
	}
	else if (x.size() < y.size())
	{
		return 1;
	}
	return 0;
}

class Node
{
  public:
	string data;
	string value;
	Node *r;
	Node *l;
	//Node *parent;
	//short int id;

  public:
	Node(const string &x)
	{
		data = x;
		value = "NULL";
		r = NULL;
		l = NULL;
		//parent = NULL;
		//id = 0;
	}
	friend class Tree;
	Node(const Node &p1)
	{
		data = p1.data;
		value = p1.value;
		r = p1.r;
		l = p1.l;
	}
	void reassign(const Node &p1)
	{
		data = p1.data;
		value = p1.value;
	}
};

class Tree
{
  public:
	Node *root;
	Tree(const string &x, const string &value)
	{
		root = new Node(x);
		root->value = value;
	}
	void add_node(string &, Node *);
	void add_node(Node *, Node *);
	Node *search(string &, Node *);
	void remove_node(string &);
	void checkBalance(Node *);
	void balance(Node *, int);
	void left_rotate(Node *);
	void right_rotate(Node *);
	int height(Node *);
	void display(Node *);
};

int Tree::height(Node *root)
{
	if (root == NULL)
	{
		return 0;
	}
	else
	{
		return 1 + max(height(root->l), height(root->r));
	}
}

void Tree::left_rotate(Node *root)
{
	Node *temp;
	if (root->l != NULL)
	{
		temp = new Node(*(root->l));
		root->l->reassign(*root);
		root->l->l = temp;
		root->l->r = root->r->l;
	}
	else
	{
		temp = new Node("new");
		temp->reassign(*root);
		root->l = temp;
	}
	root->reassign(*(root->r));
	Node *p = root->r;
	root->r = root->r->r;
	delete p;
}

void Tree::right_rotate(Node *root)
{
	Node *temp;
	if (root->r != NULL)
	{
		temp = new Node(*(root->l));
		root->r->reassign(*root);
		root->r->r = temp;
		root->r->l = root->l->r;
	}
	else
	{
		temp = new Node("new");
		temp->reassign(*root);
		root->r = temp;
	}
	root->reassign(*(root->l));
	Node *p = root->l;
	root->l = root->l->l;
	delete p;
}

Node *Tree::search(string &key, Node *root)
{
	if (root != NULL)
	{
		int side = compare(key, root->data);
		if (side == 0)
		{
			return root;
		}
		else
		{
			if (side == 1)
			{
				search(key, root->l);
			}
			else
			{
				search(key, root->r);
			}
		}
	}
	else
	{
		std::cout << "Not present in tree!\n";
		return NULL;
	}
}

void Tree::checkBalance(Node *root)
{
	if (root != NULL)
	{
		int diff = height(root->l) - height(root->r);
		if (abs(diff) >= 2)
		{
			if (diff > 0)
			{
				Node *p = root->l;
				int diff = height(p->l) - height(p->r);
				if (diff > 0) //LL rotation
				{
					balance(root, 0);
				}
				else //LR rotation
				{
					balance(root, 1);
				}
			}
			else
			{
				Node *p = root->r;
				int diff = height(p->l) - height(p->r);
				if (diff > 0) //RL rotation
				{
					balance(root, 2);
				}
				else //RR rotation
				{
					balance(root, 3);
				}
			}
		}
	}
}

void Tree::balance(Node *root, int option)
{
	switch (option)
	{
	case 0: // LL rotation
		right_rotate(root);
		break;
	case 1: //LR rotation
		left_rotate(root->l);
		right_rotate(root);
		break;
	case 2: //RL rotation
		right_rotate(root->r);
		left_rotate(root);
		break;
	case 3: //RR roation
		left_rotate(root);
		break;
	}
}

void Tree::add_node(string &key, Node *root)
{
	int side = compare(key, root->data);
	if (side == 0)
	{
		std::cout << "Given key is already present!\n";
	}
	else
	{
		if (side == 1)
		{
			if (root->l != NULL)
			{
				add_node(key, root->l);
			}
			else
			{
				root->l = new Node(key);
				// root->l->id = 1;
				// root->l->parent = root;
				std::cout << "Enter Value :";
				string value;
				std::getline(cin, value);
				root->l->value = value;
			}
		}
		else
		{
			if (root->r != NULL)
			{
				add_node(key, root->r);
			}
			else
			{
				root->r = new Node(key);
				// root->r->id = 2;
				// root->r->parent = root;
				std::cout << "Enter Value :";
				string value;
				std::getline(cin, value);
				root->r->value = value;
			}
		}
		checkBalance(root);
	}
}

void Tree::add_node(Node *current, Node *root)
{
	int side = compare(current->data, root->data);
	if (side == 0)
	{
		std::cout << "given key is already present!\n";
	}
	else
	{
		if (side == 1)
		{
			if (root->l != NULL)
			{
				add_node(current, root->l);
			}
			else
			{
				root->l = current;
				// root->l->id = 1;
				// root->l->parent = root;
			}
		}
		else
		{
			if (root->r != NULL)
			{
				add_node(current, root->r);
			}
			else
			{
				root->r = current;
				// root->r->id = 2;
				// root->r->parent = root;
			}
		}
		checkBalance(root);
	}
}

void Tree::remove_node(string &key)
{
	queue<Node *> nodes;
	nodes.push(this->root);
	Node *q = this->root;
	Node *p;
	while (!nodes.empty())
	{
		q = nodes.front();
		nodes.pop();
		if (q->l != NULL && q->l->data == key)
		{
			p = q->l;
			q->l = NULL;
			break;
		}
		else if (q->l != NULL)
		{
			nodes.push(q->l);
		}

		if (q->r != NULL && q->r->data == key)
		{
			p = q->r;
			q->r = NULL;
			break;
		}
		else if (q->r != NULL)
		{
			nodes.push(q->r);
		}
	}

	if (p != NULL)
	{
		add_node(p->l, this->root);
		add_node(p->r, this->root);
		delete p;
	}
	else
	{
		std::cout << "Requested key is not in the Dictionay!\n";
	}
}

void Tree::display(Node *root)
{
	std::cout << root->data << "\n";
	if (root->l != NULL)
	{
		display(root->l);
	}
	if (root->r != NULL)
	{
		display(root->r);
	}
}

void Upper(string &key)
{
	for (int i = 0; i < key.size(); i++)
	{
		if ('a' <= key[i] <= 'z')
		{
			key[i] -= 32;
		}
	}
}
int main()
{
	std::cout << "Initialize Tree\nGive key value pair for root node\nKey : ";
	string s1, s2;
	std::getline(cin, s1);
	Upper(s1);
	std::cout << "Value :\n";
	std::getline(cin, s2);
	Tree t(s1, s2);
	Node *p;
	while (true)
	{
		char choice;
		std::cout << "1.Add a new Entry\n2.Delete Existing Entry\n3.Search for a key\n4.Display Tree in pre-order Traversal\n5.Height of Tree\n6.Exit\n";
		cin >> choice;
		cin.ignore();
		switch (choice)
		{
		case '1':
			std::cout << "Enter Key:\n";
			std::getline(cin, s1);
			Upper(s1);
			t.add_node(s1, t.root);
			break;
		case '2':
			std::cout << "Enter Key:\n";
			std::getline(cin, s1);
			Upper(s1);
			t.remove_node(s1);
			break;
		case '3':
			std::cout << "Enter Key:\n";
			std::getline(cin, s1);
			Upper(s1);
			p = t.search(s1, t.root);
			if (p != NULL)
			{
				std::cout << "value for given key is :" << p->value << "\n";
			}
			break;
		case '4':
			t.display(t.root);
			std::cout << "\n";
			break;
		case '5':
			std::cout << "\nHeight of tree is :" << t.height(t.root) << "\n";
			break;
		case '6':
			exit(1);
			break;
		default:
			cout << "Please enter valid choice!\n";
		}
	}
	t.display(t.root);
}
/*
 OUTPUT:-
 (base) kushal@kushal-Nitro-AN515-31:src$ cd "/home/kushal/eclipse-workspace/ADSL8/src/" && g++ ADSL8.cpp -o ADSL8 && "/home/kushal/eclipse-workspace/ADSL8/src/"ADSL8
Initialize Tree
Give key value pair for root node
Key : mango
Value :
fruit
1.Add a new Entry
2.Delete Existing Entry
3.Search for a key
4.Display Tree in pre-order Traversal
5.Height of Tree
6.Exit
1
Enter Key:
apple
Enter Value :fruit
1.Add a new Entry
2.Delete Existing Entry
3.Search for a key
4.Display Tree in pre-order Traversal
5.Height of Tree
6.Exit
1
Enter Key:
tiger
Enter Value :animal
1.Add a new Entry
2.Delete Existing Entry
3.Search for a key
4.Display Tree in pre-order Traversal
5.Height of Tree
6.Exit
1
Enter Key:
bat
Enter Value :toy
1.Add a new Entry
2.Delete Existing Entry
3.Search for a key
4.Display Tree in pre-order Traversal
5.Height of Tree
6.Exit
4
MANGO
APPLE
BAT
TIGER

1.Add a new Entry
2.Delete Existing Entry
3.Search for a key
4.Display Tree in pre-order Traversal
5.Height of Tree
6.Exit
1
Enter Key:
cat
Enter Value :animal
1.Add a new Entry
2.Delete Existing Entry
3.Search for a key
4.Display Tree in pre-order Traversal
5.Height of Tree
6.Exit
4
MANGO
BAT
APPLE
CAT
TIGER

1.Add a new Entry
2.Delete Existing Entry
3.Search for a key
4.Display Tree in pre-order Traversal
5.Height of Tree
6.Exit
3
Enter Key:
bat
value for given key is :toy
1.Add a new Entry
2.Delete Existing Entry
3.Search for a key
4.Display Tree in pre-order Traversal
5.Height of Tree
6.Exit
5

Height of tree is :3
1.Add a new Entry
2.Delete Existing Entry
3.Search for a key
4.Display Tree in pre-order Traversal
5.Height of Tree
6.Exit
2
Enter Key:
bat
1.Add a new Entry
2.Delete Existing Entry
3.Search for a key
4.Display Tree in pre-order Traversal
5.Height of Tree
6.Exit
4
MANGO
APPLE
CAT
TIGER

1.Add a new Entry
2.Delete Existing Entry
3.Search for a key
4.Display Tree in pre-order Traversal
5.Height of Tree
6.Exit
6
(base) kushal@kushal-Nitro-AN515-31:src$ 
 */