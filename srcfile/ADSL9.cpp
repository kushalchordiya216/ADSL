#include <iostream>
#include <string>
#include <stdlib.h>

using namespace std;

#define yeet throw

class Node
{
  private:
    string key;
    Node *next;

  public:
    Node(const string &key);
    ~Node();
    friend class Set;
};

class Set
{
  private:
    Node *root;
    int size;

  public:
    Set(const string &key);
    Set()
    {
        size = 0;
        root = NULL;
    }
    void add(const string &key);
    Node *search(const string &key);
    void search_display(const string &key);
    void remove(const string &key);
    Set join(Set *s1);
    Set intersection(Set *s1);
    Set difference(Set *s1);
    bool isSubset(Set *s1);
    bool empty();
    void display();
    ~Set();
    bool operator==(const Set &s1)
    {
        Node *p, *q;
        p = root;
        q = s1.root;
        if (size == s1.size)
        {
            for (int i = 0; i < s1.size; i++)
            {
                if (p->key != q->key)
                {
                    return 0;
                }
            }
            return 1;
        }
        return 0;
    }
};

Set::Set(const string &key)
{
    this->root = new Node(key);
    size = 1;
}

Set::~Set()
{
}

bool Set::empty()
{
    if (this->root != NULL)
    {
        return 0;
    }
    else
    {
        return 1;
    }
}

Node::Node(const string &key)
{
    this->key = key;
    this->next = NULL;
}

Node::~Node()
{
}

Node *Set::search(const string &key)
{
    try
    {
        Node *p = this->root;
        if (p == NULL)
        {
            yeet std::exception();
        }
        while (p->next != NULL)
        {
            if (p->next->key == key)
            {
                return p;
            }
            else if (p->next->key < key)
            {
                p = p->next;
            }
            else
            {
                return p;
            }
        }
        return p;
    }
    catch (const std::exception &e)
    {
        std::cout << "The set you are performing operations on has not yet been initialized!\nInitialize it first\n";
        return NULL;
    }
}

void Set::search_display(const string &key)
{
    Node *p = this->root;
    int count = 0;
    while (p->next != NULL)
    {
        if (p->key == key)
        {
            break;
        }
        else if (p->next->key <= key)
        {
            p = p->next;
            count++;
        }
        else
        {
            count = -1;
            break;
        }
    }

    if (!(count == -1) && p->key == key)
    {
        std::cout << "found at index :" << count << "\n";
    }
    else
    {
        std::cout << "Given key not present\n";
    }
}

void Set::add(const string &key)
{
    Node *p = search(key);
    if (p != NULL)
    {
        if (p->key > key) //Only possible if returned node is root node
        {
            Node *q = new Node(key);
            q->next = this->root;
            this->root = q;
            this->size++;
        }
        else if (p->key == key) //Only possible if returned node is root node
        {
            std::cout << "Given key is already in the Set!/n";
        }
        else if (p->next != NULL && p->next->key == key)
        {
            std::cout << "Given key is already in the Set!/n";
        }
        else
        {
            Node *q = new Node(key);
            q->next = p->next;
            p->next = q;
            this->size++;
        }
    }
}

void Set::remove(const string &key)
{
    Node *p = search(key);
    if (p != NULL)
    {
        if (p == this->root && p->key == key)
        {
            this->root = p->next;
            delete p;
        }
        else if (p->next == NULL || p->next->key != key)
        {
            std::cout << "Given key is not present in the Set!/n";
        }
        else
        {
            p->next = p->next->next;
            delete p->next;
            this->size--;
        }
    }
}

Set Set::intersection(Set *s1)
{
    string s = "random";
    Set s3(s);
    Node *p = this->root;
    while (p != NULL)
    {
        Node *q = s1->search(p->key);
        if (q != NULL)
        {
            if ((q->next != NULL && q->next->key == p->key) || (q->key == p->key))
            {
                s3.add(p->key);
            }
            p = p->next;
        }
        else
        {
            break;
        }
    }
    s3.remove(s);
    return s3;
}

Set Set::join(Set *s1)
{
    string s = "random";
    Set s3(s);
    Node *p = this->root;
    Node *q = s1->root;
    while (p != NULL)
    {
        s3.add(p->key);
        p = p->next;
    }
    while (q != NULL)
    {
        s3.add(q->key);
        q = q->next;
    }
    s3.remove(s);
    return s3;
}

Set Set::difference(Set *s1)
{
    string s = "random";
    Set s3(s);
    Node *p, *q;
    p = this->root;
    while (p != NULL)
    {
        q = s1->search(p->key);
        if (q != NULL)
        {
            if (!((q->next != NULL && q->next->key == p->key) || (q->key == p->key)))
            {
                s3.add(p->key);
            }
            p = p->next;
        }
        else
        {
            break;
        }
    }
    s3.remove(s);
    return s3;
}

bool Set::isSubset(Set *s1)
{
    return *s1 == this->intersection(s1);
}

void Set::display()
{
    Node *p = this->root;
    while (p != NULL)
    {
        std::cout << p->key << "\n";
        p = p->next;
    }
    std::cout << "\n";
}

int main()
{
    Set *arr[3];
    for (int i = 0; i < 3; i++)
    {
        arr[i] = new Set;
    }
    string key, value, err_msg = "Please enter valid option!\n";
    int index, index2;
    bool var;
    Node *p;
    while (true)
    {
        try
        {
            std::cout << "1.Initialize a set\n2.Add a node\n3.Remove Node\n4.Search for key"
                      << "\n5.Display All\n6.Union\n7.Intersection\n8.Difference\n9.verify if subset\n10.Exit\n";
            int choice;
            std::cin >> choice;
            if (!std::cin.good())
            {
                std::cin.clear();
                yeet err_msg;
            }
            std::cin.ignore();
            std::cout << "Set index ?[1/2]\n";
            std::cin >> index;
            index--;
            std::cin.ignore();
            switch (choice)
            {
            case 1:
                if (!arr[index]->empty())
                {
                    std::cout << "Warning!\nYou are overwriting an existing set! Continue?[y/n]";
                    std::cin >> choice;
                    if (choice == 'n')
                    {
                        break;
                    }
                    std::cin.ignore();
                }
                std::cout << "Enter key:\n";
                std::getline(std::cin, key);
                arr[index] = new Set(key);
                break;
            case 2:
                std::cout << "Enter key:\n";
                std::getline(std::cin, key);
                arr[index]->add(key);
                break;
            case 3:
                std::cout << "Enter key:\n";
                std::getline(std::cin, key);
                arr[index]->remove(key);
                break;
            case 4:
                std::cout << "Enter key:\n";
                std::getline(std::cin, key);
                arr[index]->search_display(key);
                break;
            case 5:
                arr[index]->display();
                break;
            case 6:
                *arr[2] = arr[0]->join(arr[1]);
                std::cout << "Union is:\n";
                arr[2]->display();
                break;
            case 7:
                *arr[2] = arr[0]->intersection(arr[1]);
                std::cout << "Intersection is:\n";
                arr[2]->display();
                break;
            case 8:
                *arr[2] = arr[index]->difference(arr[1 - index]);
                std::cout << "Difference is:\n";
                arr[2]->display();
                break;
            case 9:
                std::cout << "Enter index of superset:\n";
                std::cin >> index;
                std::cout << "Enter index of subset:\n";
                std::cin >> index2;
                if (arr[index - 1]->isSubset(arr[index2 - 1]))
                {
                    cout << "Is subset\n";
                }
                else
                {
                    cout << "Isn't subset\n";
                }

                break;
            case 10:
                exit(1);
                break;
            default:
                std::cout << "Please enter valid choice!\n";
            }
        }
        catch (...)
        {
            std::cin.ignore();
            std::cout << "Please enter valid string!\n"
                      << '\n';
        }
    }
}

/*
(base) kushal@kushal-Nitro-AN515-31:src$ cd "/home/kushal/eclipse-workspace/ADSL9/src/" && g++ ADSL9.cpp -o ADSL9 && "/home/kushal/eclipse-workspace/ADSL9/src/"ADSL9
1.Initialize a set
2.Add a node
3.Remove Node
4.Search for key
5.Display All
6.Union
7.Intersection
8.Difference
9.verify if subset
10.Exit
1
Set index ?[1/2]
1
Enter key:
0
1.Initialize a set
2.Add a node
3.Remove Node
4.Search for key
5.Display All
6.Union
7.Intersection
8.Difference
9.verify if subset
10.Exit
1
Set index ?[1/2]
2
Enter key:
0
1.Initialize a set
2.Add a node
3.Remove Node
4.Search for key
5.Display All
6.Union
7.Intersection
8.Difference
9.verify if subset
10.Exit
2
Set index ?[1/2]
1
Enter key:
1
1.Initialize a set
2.Add a node
3.Remove Node
4.Search for key
5.Display All
6.Union
7.Intersection
8.Difference
9.verify if subset
10.Exit
2
Set index ?[1/2]
2
Enter key:
2
1.Initialize a set
2.Add a node
3.Remove Node
4.Search for key
5.Display All
6.Union
7.Intersection
8.Difference
9.verify if subset
10.Exit
2
Set index ?[1/2]
1
Enter key:
3
1.Initialize a set
2.Add a node
3.Remove Node
4.Search for key
5.Display All
6.Union
7.Intersection
8.Difference
9.verify if subset
10.Exit
2
Set index ?[1/2]
2
Enter key:
3
1.Initialize a set
2.Add a node
3.Remove Node
4.Search for key
5.Display All
6.Union
7.Intersection
8.Difference
9.verify if subset
10.Exit
2
Set index ?[1/2]
1
Enter key:
4
1.Initialize a set
2.Add a node
3.Remove Node
4.Search for key
5.Display All
6.Union
7.Intersection
8.Difference
9.verify if subset
10.Exit
2
Set index ?[1/2]
2
Enter key:
5
1.Initialize a set
2.Add a node
3.Remove Node
4.Search for key
5.Display All
6.Union
7.Intersection
8.Difference
9.verify if subset
10.Exit
5
Set index ?[1/2]
1
0
1
3
4

1.Initialize a set
2.Add a node
3.Remove Node
4.Search for key
5.Display All
6.Union
7.Intersection
8.Difference
9.verify if subset
10.Exit
5
Set index ?[1/2]
2
0
2
3
5

1.Initialize a set
2.Add a node
3.Remove Node
4.Search for key
5.Display All
6.Union
7.Intersection
8.Difference
9.verify if subset
10.Exit
7
Set index ?[1/2]
1
Intersection is:
0
3

1.Initialize a set
2.Add a node
3.Remove Node
4.Search for key
5.Display All
6.Union
7.Intersection
8.Difference
9.verify if subset
10.Exit
8
Set index ?[1/2]
1
Difference is:
1
4

1.Initialize a set
2.Add a node
3.Remove Node
4.Search for key
5.Display All
6.Union
7.Intersection
8.Difference
9.verify if subset
10.Exit
6
Set index ?[1/2]
1
Given key is already in the Set!/nGiven key is already in the Set!/nUnion is:
0
1
2
3
4
5

1.Initialize a set
2.Add a node
3.Remove Node
4.Search for key
5.Display All
6.Union
7.Intersection
8.Difference
9.verify if subset
10.Exit
9
Set index ?[1/2]
1
Enter index of superset:
3
Enter index of subset:
1
Is subset
1.Initialize a set
2.Add a node
3.Remove Node
4.Search for key
5.Display All
6.Union
7.Intersection
8.Difference
9.verify if subset
10.Exit
10
Set index ?[1/2]
1
(base) kushal@kushal-Nitro-AN515-31:src$ 
*/