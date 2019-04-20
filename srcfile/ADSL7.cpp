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
	string value = "Not Present!";
	string symbol = "NULL";
	int next = 0;
	int prev = 0;

  public:
	friend class HashTable;
};

class HashTable
{
	HashNode hashes[30];

  public:
	int hash(string name);
	void insert(string number, string name);
	void remove(string name);
	int search(string name);
	void replacement(int index, string name, string number);
	void modify(string name);
	void display();
};

void HashTable::display()
{
	for (int i = 0; i < 30; i++)
	{
		if (hashes[i].value != "Not Present!")
		{
			cout << hashes[i].symbol << " " << hashes[i].value << "\n";
		}
	}
}

int HashTable::hash(string name)
{
	int index = ((int)name[0]) % 30;
	return index + 1;
}

void HashTable::insert(string number, string name)
{
	int index = hash(name);

	if (hashes[index].value == "Not Present!")
	{
		hashes[index].value = number;
		hashes[index].symbol = name;
	}
	else
	{
		if (hashes[index].symbol[0] == name[0])
		{
			while (hashes[index].next != 0)
			{
				index = hashes[index].next;
			}
			for (int i = 1; i < 30; i++)
			{
				if (hashes[i].value == "Not Present!")
				{
					hashes[i].value = number;
					hashes[index].next = i;
					hashes[i].prev = index;
					hashes[i].symbol = name;
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
	for (int i = 1; i < 30; i++)
	{
		if (hashes[i].value == "Not Present!")
		{
			hashes[i].value = hashes[index].value;
			hashes[hashes[index].prev].next = i;
			hashes[i].symbol = hashes[index].symbol;
			break;
		}
	}
	hashes[index].value = number;
	hashes[index].symbol = name;
	hashes[index].next = 0;
	hashes[index].prev = 0;
}

int HashTable::search(string name)
{
	int index = hash(name);
	while (hashes[index].symbol != name && index != 0)
	{
		index = hashes[index].next;
	}
	cout << "Value is : " << hashes[index].value << "\n\n\n";
	return index;
}

void HashTable::remove(string name)
{
	int index = search(name);
	if (index != 0)
	{
		hashes[index].symbol = "NULL";
		hashes[index].value = "Not Present!";
		hashes[hashes[index].prev].next = hashes[index].next;
		hashes[index].prev = 0;
	}
	else
	{
		cout << "It's Not present in the first place!\n";
	}
}

void HashTable::modify(string name)
{
	int index = search(name);
	if (index == 0)
	{
		cout << "Requested symbol does not exist in the table!\nWould you like to add it?[Y/n] ";
		char choice;
		cin >> choice;
		if (choice == 'Y' || choice == 'y')
		{
			cout << "Enter corresponding value:";
			string number;
			getline(cin, number);
			insert(name, number);
		}
		else
			return;
	}
	else
	{
		cout << "Enter new value";
		string number;
		cin >> number;
		hashes[index].value = number;
	}
}

int main()
{
	HashTable h;
	string name, number;
	int index;
	while (true)
	{
		cout << "1.Insert New Entry\n2.Delete Existing Entry\n3.Search Existing Entry\n4.Update Values\n5.Exit\n";
		char choice;
		cin >> choice;
		switch (choice)
		{
		case '1':
			cin.ignore();
			cout << "symbol: ";
			getline(cin, name);
			cout << "value: ";
			getline(cin, number);
			h.insert(number, name);
			break;
		case '2':
			cin.ignore();
			cout << "symbol: ";
			getline(cin, name);
			h.remove(name);
			break;
		case '3':
			cin.ignore();
			cout << "symbol: ";
			getline(cin, name);
			index = h.search(name);
			break;
		case '4':
			cin.ignore();
			cout << "symbol: ";
			getline(cin, name);
			h.modify(name);
			break;
		case '5':
			exit(1);
			break;
		default:
			cout << "invalid choice!\nPlease Enter Valid Choice\n";
		}
	}
}
/*
 OUTPUT:-
 (base) kushal@kushal-Nitro-AN515-31:src$ cd "/home/kushal/eclipse-workspace/ADSL7/src/" && g++ ADSL7.cpp -o ADSL7 && "/home/kushal/eclipse-workspace/ADSL7/src/"ADSL7
1.Insert New Entry
2.Delete Existing Entry
3.Search Existing Entry
4.Update Values
5.Exit
1
symbol: *
value: Multiplication
1.Insert New Entry
2.Delete Existing Entry
3.Search Existing Entry
4.Update Values
5.Exit
1
symbol: +
value: addition
1.Insert New Entry
2.Delete Existing Entry
3.Search Existing Entry
4.Update Values
5.Exit
1
symbol: -
value: subtraction
1.Insert New Entry
2.Delete Existing Entry
3.Search Existing Entry
4.Update Values
5.Exit
1
symbol: \
value: division
1.Insert New Entry
2.Delete Existing Entry
3.Search Existing Entry
4.Update Values
5.Exit
3
symbol: *
Value is : Multiplication


1.Insert New Entry
2.Delete Existing Entry
3.Search Existing Entry
4.Update Values
5.Exit
4
symbol: *
Value is : Multiplication


Enter new valueAstersik
1.Insert New Entry
2.Delete Existing Entry
3.Search Existing Entry
4.Update Values
5.Exit
3
symbol: *
Value is : Astersik


1.Insert New Entry
2.Delete Existing Entry
3.Search Existing Entry
4.Update Values
5.Exit
2
symbol: +
Value is : addition


1.Insert New Entry
2.Delete Existing Entry
3.Search Existing Entry
4.Update Values
5.Exit
3
symbol: +
Value is : Not Present!


1.Insert New Entry
2.Delete Existing Entry
3.Search Existing Entry
4.Update Values
5.Exit
5
(base) kushal@kushal-Nitro-AN515-31:src$ 
 */