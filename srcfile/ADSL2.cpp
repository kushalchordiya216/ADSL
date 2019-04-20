//============================================================================
// Name        : ADSL2.cpp
// Author      : kushal
// Version     :
// Copyright   : Your copyright notice
// Description : A Dictionary stores keywords & its meanings.
//				 Provide facility for adding new keywords, deleting
//				 keywords, updating values of any entry, assign a
//				 given tree into another tree (=). Provide facility
//				 to display whole data sorted in ascending/ Descending
//				 order. Also find how many maximum comparisons may
//				 require for finding any keyword.
//				 Use Binary Search Tree for implementation
//============================================================================

#include <iostream>
#include <string>
#include <stdlib.h>
using namespace std;

class Node
{
  public:
	string meaning, key;
	Node *rchild, *lchild, *parent;
	Node()
	{
		rchild = NULL;
		lchild = NULL;
		parent = NULL;
	}
};

class Tree
{
  public:
	Node *root;
	void init(string, string);
	void add(string, string);
	void remove(string);
	void display(Node *);
	Node *find(string);
	void change(string);
};

void Tree::change(string key)
{
	Node *p = new Node;
	string meaning;
	p = find(key);
	if (p->key.size() != 0)
	{
		cout << "1.Add another meaning\n2.Replace current meaning(s)";
		int x;
		cin >> x;
		cout << "Enter New meaning :-\n";
		cin.ignore();
		getline(cin, meaning);
		switch (x)
		{
		case 1:
			p->meaning = p->meaning + "\n" + meaning;
			break;
		case 2:
			p->meaning = meaning;
			break;
		default:
			cout << "Please enter valid option!\n";
		}
	}
	else
	{
		cout << "No matches Found!";
	}
}
int compare(string s1, string s2)
{
	int size1 = s1.size(), size2 = s2.size();
	int i = 0;
	do
	{
		if (s1[i] > s2[i])
		{
			return 1;
		}
		else if (s1[i] < s2[i])
		{
			return -1;
		}
		else
		{
			i++;
		}
	} while (i < min(size1, size2));
	return 0;
}

Node *Tree::find(string key)
{
	Node *p = new Node;
	Node *q = new Node;
	p = root;
	int x;
	do
	{
		x = compare(key, p->key);
		if (x < 0)
		{
			if (p->lchild != NULL)
			{
				p = p->lchild;
			}
			else
			{
				cout << "Word you are looking for doesn't exist in Dictionary!\n";
				return q;
			}
		}
		else if (x > 0)
		{
			if (p->rchild != NULL)
			{
				p = p->rchild;
			}
			else
			{
				cout << "Word you are looking for doesn't exist in Dictionary!\n";
				return q;
			}
		}
		else
		{
			return p;
		}
	} while (true);
	return q;
}
void Tree::init(string key, string meaning)
{
	root = new Node;
	root->key = key;
	root->meaning = meaning;
}

void Tree::add(string key, string meaning)
{
	Node *p = new Node;
	p = root;
	while (true)
	{
		int x = compare(key, p->key);
		if (x > 0)
		{
			if (p->rchild == NULL)
			{
				Node *q = new Node;
				p->rchild = q;
				q->parent = p;
				q->key = key;
				q->meaning = meaning;
				return;
			}
			else
			{
				p = p->rchild;
			}
		}
		else if (x < 0)
		{
			if (p->lchild == NULL)
			{
				Node *q = new Node;
				p->lchild = q;
				q->parent = p;
				q->key = key;
				q->meaning = meaning;
				return;
			}
			else
			{
				p = p->lchild;
			}
		}
		else
		{
			cout << "THE GIVEN KEYWORD IS ALREADY INCLUDED IN THE DICTIONARY!\n";
			return;
		}
	};
}

void Tree::remove(string key)
{
	Node *p = new Node;
	p = root;
	int marker;
	while (true)
	{
		int x = compare(key, p->key);
		if (x > 0)
		{
			p = p->rchild;
			marker = 1;
		}
		else if (x < 0)
		{
			p = p->lchild;
			marker = 2;
		}
		else
		{
			Node *q = new Node;
			if (marker == 2)
			{
				if (p->lchild != NULL)
				{
					p->parent->lchild = p->lchild;
					p->lchild->parent = p->parent;
					q = p->lchild;
					if (p->rchild != NULL)
					{
						while (q->rchild != NULL)
						{
							q = q->rchild;
						}
						q->rchild = p->rchild;
					}
					delete p;
					return;
				}
				else if (p->rchild != NULL)
				{
					p->parent->lchild = p->rchild;
					p->rchild->parent = p->parent;
					delete p;
					return;
				}
				else
				{
					delete p;
					return;
				}
			}
			else if (marker == 1)
			{
				if (p->rchild != NULL)
				{
					p->parent->rchild = p->rchild;
					p->rchild->parent = p->parent;
					q = p->rchild;
					if (p->lchild != NULL)
					{
						while (q->lchild != NULL)
						{
							q = q->lchild;
						}
						q->lchild = p->lchild;
					}
					delete p;
					return;
				}
				else if (p->lchild != NULL)
				{
					p->parent->rchild = p->lchild;
					p->lchild->parent = p->parent;
					delete p;
					return;
				}
				else
				{
					delete p;
					return;
				}
			}
		}
	}
}

void Tree::display(Node *p)
{
	if (p->lchild != NULL)
	{
		display(p->lchild);
	}
	cout << p->key << "\n";
	if (p->rchild != NULL)
	{
		display(p->rchild);
	}
}

int main()
{
	Tree t;
	Node *p = new Node;
	cout << "Initialize Dictionary:\n";
	string key, meaning;
	getline(cin, key);
	getline(cin, meaning);
	t.init(key, meaning);
	int choice;
	do
	{
		cout << "1.Find meaning of a keyword\n2.Add a Key-Word\n3.Remove A Key-Word\n4.Display in ascending order\n5.Update meanings\n6.Exit\n";
		cin >> choice;
		switch (choice)
		{
		case 1:
			cout << "Enter key word here:\n";
			cin.ignore();
			getline(cin, key);
			p = t.find(key);
			if (p->key.size() > 0)
			{
				cout << "Meaning of given word is :-\n";
				cout << p->meaning << "\n";
			}
			else
			{
				cout << "No matches for requested word!\n";
			}
			break;
		case 2:
			cout << "Enter Key-Word:\n";
			cin.ignore();
			getline(cin, key);
			cout << "Enter Meaning:\n";
			getline(cin, meaning);
			t.add(key, meaning);
			break;
		case 3:
			cout << "Enter the Key-Word:\n";
			cin.ignore();
			getline(cin, key);
			p = t.find(key);
			if (p->key.size() > 0)
			{
				t.remove(key);
			}
			break;
		case 4:
			t.display(t.root);
			break;
		case 5:
			cout << "Enter key-word for which you want to change meaning :\n";
			cin.ignore();
			getline(cin, key);
			t.change(key);
			break;
		case 6:
			exit(1);
		default:
			cout << "Please enter valid Choice!\n";
		}
	} while (true);
	return 0;
}

/*
OUTPUT:-
(base) kushal@kushal-Nitro-AN515-31:src$ cd "/home/kushal/eclipse-workspace/ADSL2/src/" && g++ ADSL2.cpp -o ADSL2 && "/home/kushal/eclipse-workspace/ADSL2/src/"ADSL2
Initialize Dictionary:
mango
fruit
1.Find meaning of a keyword
2.Add a Key-Word
3.Remove A Key-Word
4.Display in ascending order
5.Update meanings
6.Exit
2
Enter Key-Word:
ant
Enter Meaning:
insect
1.Find meaning of a keyword
2.Add a Key-Word
3.Remove A Key-Word
4.Display in ascending order
5.Update meanings
6.Exit
2
Enter Key-Word:
tiger
Enter Meaning:
animal
1.Find meaning of a keyword
2.Add a Key-Word
3.Remove A Key-Word
4.Display in ascending order
5.Update meanings
6.Exit
4
ant
mango
tiger
1.Find meaning of a keyword
2.Add a Key-Word
3.Remove A Key-Word
4.Display in ascending order
5.Update meanings
6.Exit
1
Enter key word here:
mango
Meaning of given word is :-
fruit
1.Find meaning of a keyword
2.Add a Key-Word
3.Remove A Key-Word
4.Display in ascending order
5.Update meanings
6.Exit
5
Enter key-word for which you want to change meaning :
tiger
1.Add another meaning
2.Replace current meaning(s)2
Enter New meaning :-
wild animal
1.Find meaning of a keyword
2.Add a Key-Word
3.Remove A Key-Word
4.Display in ascending order
5.Update meanings
6.Exit
2
Enter Key-Word:
bat
Enter Meaning:
toy
1.Find meaning of a keyword
2.Add a Key-Word
3.Remove A Key-Word
4.Display in ascending order
5.Update meanings
6.Exit
4
ant
bat
mango
tiger
1.Find meaning of a keyword
2.Add a Key-Word
3.Remove A Key-Word
4.Display in ascending order
5.Update meanings
6.Exit
3
Enter the Key-Word:
tiger
1.Find meaning of a keyword
2.Add a Key-Word
3.Remove A Key-Word
4.Display in ascending order
5.Update meanings
6.Exit
1
Enter key word here:
tiger
Word you are looking for doesn't exist in Dictionary!
No matches for requested word!
1.Find meaning of a keyword
2.Add a Key-Word
3.Remove A Key-Word
4.Display in ascending order
5.Update meanings
6.Exit
4
ant
bat
mango

1.Find meaning of a keyword
2.Add a Key-Word
3.Remove A Key-Word
4.Display in ascending order
5.Update meanings
6.Exit
6
(base) kushal@kushal-Nitro-AN515-31:src$ 
*/