//============================================================================
// Name        : ADSL1.cpp
// Author      : kushal
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include <queue>
using namespace std;
int count = 0;

class Node
{
  public:
	Node *rchild, *lchild, *parent;
	int data;
	Node(int x)
	{
		data = x;
		lchild = NULL;
		rchild = NULL;
		parent = NULL;
	}
};

class Tree
{
  public:
	Node *root;
	void init(int);
	int height(Node *);
	void addRight();
	void addLeft();
	void preorder(Node *);
	void postorder(Node *);
	void mirror(Node *, Node *, int, int);
	void operator=(Tree &);
	void leaves(Node *, int &);
	Node *find(Node *, int);
	void display(int);
	void equate(Node *, Node *, int, int);
};

void Tree::display(int h)
{
}

Node *Tree::find(Node *p, int x)
{
	if (p->data == x)
	{
		return p;
	}
	if (p->lchild != NULL)
	{
		Node *q = find(p->lchild, x);
		if (q != NULL)
		{
			return q;
		}
	}
	if (p->rchild != NULL)
	{
		Node *q = find(p->rchild, x);
		if (q != NULL)
		{
			return q;
		}
	}
}

void Tree::leaves(Node *p, int &count)
{
	if (p->lchild != NULL)
	{
		leaves(p->lchild, count);
	}
	if (p->rchild != NULL)
	{
		leaves(p->rchild, count);
	}
	if (p->lchild == NULL && p->rchild == NULL)
	{
		count++;
	}
}

void Tree::equate(Node *p, Node *q, int h, int d)
{
	if (h < 1 && p->rchild != NULL && p->lchild != NULL)
	{
		q->lchild = new Node(p->lchild->data);
		q->rchild = new Node(p->rchild->data);
		if (p->lchild != NULL)
		{
			equate(p->lchild, q->lchild, h + 1, d);
		}
		if (p->rchild != NULL)
		{
			equate(p->rchild, q->rchild, h + 1, d);
		}
	}
}

void Tree::operator=(Tree &t)
{
	root->data = t.root->data;
	equate(t.root, root, 0, height(t.root));
}

void Tree::init(int x)
{
	root = new Node(x);
}

int Tree::height(Node *p)
{
	if (root == NULL)
	{
		return 0;
	}

	queue<Node *> q;
	q.push(root);
	int height = 0;
	while (1)
	{
		int nodeCount = q.size();
		if (nodeCount == 0)
		{
			return height;
		}
		height++;
		while (nodeCount > 0)
		{
			Node *node = q.front();
			q.pop();
			if (node->lchild != NULL)
				q.push(node->lchild);
			if (node->rchild != NULL)

				q.push(node->rchild);
			nodeCount--;
		}
	}
}

void Tree::addLeft()
{

	cout << "Enter Value of Node you want to Add child Node to: ";
	int y;
	cin >> y;
	Node *p;
	p = find(root, y);
	if (p == NULL)
	{
		cout << "THE NODE YOU WERE LOOKING FOR IS NOT PRESENT IN THE TREE!\n";
		return;
	}
	cout << "Enter Value of New Node: ";
	int x;
	cin >> x;
	if (p->lchild == NULL)
	{
		p->lchild = new Node(x);
	}
	p->lchild->data = x;
	p->lchild->parent = p;
}

void Tree::addRight()
{

	cout << "Enter Value of Node you want to Add child Node to: ";
	int y;
	cin >> y;
	Node *p;
	p = find(root, y);
	if (p == NULL)
	{
		cout << "THE NODE YOU WERE LOOKING FOR IS NOT PRESENT IN THE TREE!\n";
		return;
	}
	cout << "Enter Value of New Node: ";
	int x;
	cin >> x;
	if (p->rchild == NULL)
	{
		p->rchild = new Node(x);
	}
	p->rchild->data = x;
	p->rchild->parent = p;
}

void Tree::preorder(Node *p)
{
	cout << p->data << " ";
	if (p->lchild != NULL)
	{
		preorder(p->lchild);
	}
	if (p->rchild != NULL)
	{
		preorder(p->rchild);
	}
}

void Tree::postorder(Node *p)
{
	if (p->lchild != NULL)
	{
		postorder(p->lchild);
	}
	if (p->rchild != NULL)
	{
		postorder(p->rchild);
	}
	cout << p->data << " ";
}

void Tree::mirror(Node *p, Node *q, int h, int d)
{
	if (h < d && p->rchild != NULL && p->lchild != NULL)
	{
		q->lchild = new Node(p->rchild->data);
		q->rchild = new Node(p->lchild->data);
		if (p->lchild != NULL)
		{
			mirror(p->lchild, q->rchild, h + 1, d);
		}
		if (p->rchild != NULL)
		{
			mirror(p->rchild, q->lchild, h + 1, d);
		}
	}
}

int main()
{
	Tree t, t1;
	int h;
	cout << "Enter a Value for Root Node of Tree:\n";
	cin >> h;
	t.init(h);
	t1.init(h);
	int choice;
	while (true)
	{
		cout << "\n1.Add Left child to Node\n2.Add Right child to a Node\n3.Display Contents of Tree in Pre-Order Traversal\n4.Display Contents of Tree in Post-Order Traversal\n5.Create a Mirror Image of Given Tree\n6.Give Height of Tree\n7.Give Number of Leaf Nodes\n8.Create A Copy\n9.Exit\n";
		cin >> choice;
		switch (choice)
		{
		case 1:
			t.addLeft();
			break;
		case 2:
			t.addRight();
			break;
		case 3:
			t.preorder(t.root);
			cout << "\n";
			break;
		case 4:
			t.postorder(t.root);
			cout << "\n";
			break;
		case 5:
			t1.mirror(t.root, t1.root, 0, t.height(t.root));
			cout << "\nPre-order Traversal of mirror image is :\n";
			t1.preorder(t1.root);
			cout << "\n";
			break;
		case 6:
			cout << "Height of tree is:" << t.height(t.root) << " \n";
			break;
		case 7:
			count = 0;
			t.leaves(t.root, count);
			cout << "\nNo. of Leaf Nodes: " << count << "\n";
			break;
		case 8:
			t1.init(h);
			t1 = t;
			cout << "Postorder of copy is:\n";
			t1.postorder(t1.root);
			break;
		case 9:
			exit(1);
		default:
			cout << "Enter Valid Option!\n";
		}
	};
}

/*
OUTPUT:-
(base) kushal@kushal-Nitro-AN515-31:src$ ./ADSL1
Enter a Value for Root Node of Tree:
9

1.Add Left child to Node
2.Add Right child to a Node
3.Display Contents of Tree in Pre-Order Traversal
4.Display Contents of Tree in Post-Order Traversal
5.Create a Mirror Image of Given Tree
6.Give Height of Tree
7.Give Number of Leaf Nodes
8.Create A Copy
9.Exit
1
Enter Value of Node you want to Add child Node to: 9
Enter Value of New Node: 5

1.Add Left child to Node
2.Add Right child to a Node
3.Display Contents of Tree in Pre-Order Traversal
4.Display Contents of Tree in Post-Order Traversal
5.Create a Mirror Image of Given Tree
6.Give Height of Tree
7.Give Number of Leaf Nodes
8.Create A Copy
9.Exit
2
Enter Value of Node you want to Add child Node to: 9
Enter Value of New Node: 4

1.Add Left child to Node
2.Add Right child to a Node
3.Display Contents of Tree in Pre-Order Traversal
4.Display Contents of Tree in Post-Order Traversal
5.Create a Mirror Image of Given Tree
6.Give Height of Tree
7.Give Number of Leaf Nodes
8.Create A Copy
9.Exit
3
9 5 4 

1.Add Left child to Node
2.Add Right child to a Node
3.Display Contents of Tree in Pre-Order Traversal
4.Display Contents of Tree in Post-Order Traversal
5.Create a Mirror Image of Given Tree
6.Give Height of Tree
7.Give Number of Leaf Nodes
8.Create A Copy
9.Exit
4
5 4 9 

1.Add Left child to Node
2.Add Right child to a Node
3.Display Contents of Tree in Pre-Order Traversal
4.Display Contents of Tree in Post-Order Traversal
5.Create a Mirror Image of Given Tree
6.Give Height of Tree
7.Give Number of Leaf Nodes
8.Create A Copy
9.Exit
5

Pre-order Traversal of mirror image is :
9 4 5 

1.Add Left child to Node
2.Add Right child to a Node
3.Display Contents of Tree in Pre-Order Traversal
4.Display Contents of Tree in Post-Order Traversal
5.Create a Mirror Image of Given Tree
6.Give Height of Tree
7.Give Number of Leaf Nodes
8.Create A Copy
9.Exit
6
Height of tree is:2 

1.Add Left child to Node
2.Add Right child to a Node
3.Display Contents of Tree in Pre-Order Traversal
4.Display Contents of Tree in Post-Order Traversal
5.Create a Mirror Image of Given Tree
6.Give Height of Tree
7.Give Number of Leaf Nodes
8.Create A Copy
9.Exit
7

No. of Leaf Nodes: 2

1.Add Left child to Node
2.Add Right child to a Node
3.Display Contents of Tree in Pre-Order Traversal
4.Display Contents of Tree in Post-Order Traversal
5.Create a Mirror Image of Given Tree
6.Give Height of Tree
7.Give Number of Leaf Nodes
8.Create A Copy
9.Exit
8
Postorder of copy is:
5 4 9 
1.Add Left child to Node
2.Add Right child to a Node
3.Display Contents of Tree in Pre-Order Traversal
4.Display Contents of Tree in Post-Order Traversal
5.Create a Mirror Image of Given Tree
6.Give Height of Tree
7.Give Number of Leaf Nodes
8.Create A Copy
9.Exit
9
(base) kushal@kushal-Nitro-AN515-31:src$ 
*/