//============================================================================
// Name        : ADSL6.cpp
// Author      : kushal
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include <string>
#include <stdlib.h>

using namespace std;
class HashNode
{
	string number = "Not Present!";
	string name = "NULL";
	int next = 0;
	int prev = 0;

  public:
	friend class HashTable;
};

class HashTable
{
	HashNode hashes[27];

  public:
	int hash(string name);
	void insert(string number, string name);
	void remove(string name);
	int search(string name);
	void replacement(int index, string name, string number);
	void display();
};

void HashTable::display()
{
	for (int i = 0; i < 27; i++)
	{
		if (hashes[i].number != "Not Present!")
		{
			cout << hashes[i].name << " " << hashes[i].number << "\n";
		}
	}
}
int HashTable::hash(string name)
{
	int index = ((int)name[0]) - 64;
	if (index >= 32)
	{
		index -= 32;
	}
	return index;
}

void HashTable::insert(string number, string name)
{
	int index = hash(name);

	if (hashes[index].number == "Not Present!")
	{
		hashes[index].number = number;
		hashes[index].name = name;
	}
	else
	{
		if (hashes[index].name[0] == name[0])
		{
			while (hashes[index].next != 0)
			{
				index = hashes[index].next;
			}
			for (int i = 1; i < 27; i++)
			{
				if (hashes[i].number == "Not Present!")
				{
					hashes[i].number = number;
					hashes[index].next = i;
					hashes[i].prev = index;
					hashes[i].name = name;
					return;
				}
			}
			cout << "Sorry, Table is Full!\n";
		}
		else
		{
			replacement(index, name, number);
		}
	}
}

void HashTable::replacement(int index, string name, string number)
{
	for (int i = 1; i < 27; i++)
	{
		if (hashes[i].number == "Not Present!")
		{
			hashes[i].number = hashes[index].number;
			hashes[hashes[index].prev].next = i;
			hashes[i].name = hashes[index].name;
			break;
		}
	}
	hashes[index].number = number;
	hashes[index].name = name;
	hashes[index].next = 0;
	hashes[index].prev = 0;
}

int HashTable::search(string name)
{
	int index = hash(name);
	while (hashes[index].name != name && index != 0)
	{
		index = hashes[index].next;
	}
	cout << hashes[index].number << "\n";
	return index;
}

void HashTable::remove(string name)
{
	int index = search(name);
	if (index != 0)
	{
		hashes[index].name = "NULL";
		hashes[index].number = "Not Present!";
		hashes[hashes[index].prev].next = hashes[index].next;
		hashes[index].prev = 0;
	}
	else
	{
		cout << "It's Not present in the first place!\n";
	}
}

int main()
{
	HashTable h;
	string name, number;
	int index;
	while (true)
	{
		cout << "1.Insert New Entry\n2.Delete Existing Entry\n3.Search Existing Entry\n4.Exit\n";
		char choice;
		cin >> choice;
		switch (choice)
		{
		case '1':
			cin.ignore();
			cout << "Key: ";
			getline(cin, name);
			cout << "Value: ";
			getline(cin, number);
			h.insert(number, name);
			break;
		case '2':
			cin.ignore();
			cout << "Key: ";
			getline(cin, name);
			h.remove(name);
			break;
		case '3':
			cin.ignore();
			cout << "Key: ";
			getline(cin, name);
			index = h.search(name);
			break;
		case '4':
			exit(1);
			break;
		default:
			cout << "invalid choice!\n";
		}
	}
}
/*
 OUTPUT:- 
 (base) kushal@kushal-Nitro-AN515-31:src$ cd "/home/kushal/eclipse-workspace/ADSL6/src/" && g++ ADSL6.cpp -o ADSL6 && "/home/kushal/eclipse-workspace/ADSL6/src/"ADSL6
1.Insert New Entry
2.Delete Existing Entry
3.Search Existing Entry
4.Exit
1
Key: kushal
Value: 9420425495
1.Insert New Entry
2.Delete Existing Entry
3.Search Existing Entry
4.Exit
1
Key: nikhil
Value: 9930433290
1.Insert New Entry
2.Delete Existing Entry
3.Search Existing Entry
4.Exit
1
Key: kunal
Value: 8080574332
1.Insert New Entry
2.Delete Existing Entry
3.Search Existing Entry
4.Exit
1
Key: anand
Value: 7786708332
1.Insert New Entry
2.Delete Existing Entry
3.Search Existing Entry
4.Exit
3
Key: anand
7786708332
1.Insert New Entry
2.Delete Existing Entry
3.Search Existing Entry
4.Exit
3
Key: kushal
9420425495
1.Insert New Entry
2.Delete Existing Entry
3.Search Existing Entry
4.Exit
3
Key: sanya
Not Present!
1.Insert New Entry
2.Delete Existing Entry
3.Search Existing Entry
4.Exit
2
Key: nikhil
9930433290
1.Insert New Entry
2.Delete Existing Entry
3.Search Existing Entry
4.Exit
3
Key: nikhil
Not Present!
1.Insert New Entry
2.Delete Existing Entry
3.Search Existing Entry
4.Exit
4
(base) kushal@kushal-Nitro-AN515-31:src$ 
 */