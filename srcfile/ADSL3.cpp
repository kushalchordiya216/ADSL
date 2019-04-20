//============================================================================
// Name        : ADSL3.CPP
// Author      : kushal
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include <queue>
using namespace std;

class Node
{
  public:
    int key;
    Node *left, *right;
    bool isThreaded;
};

Node *createThreaded(Node *root)
{
    if (root == NULL)
    {
        return NULL;
    }
    if (root->left == NULL &&
        root->right == NULL)
    {
        return root;
    }
    if (root->left != NULL)
    {
        Node *l = createThreaded(root->left);
        l->right = root;
        l->isThreaded = true;
    }
    if (root->right == NULL)
    {
        return root;
    }
    return createThreaded(root->right);
}

Node *leftMost(Node *root)
{
    while (root != NULL && root->left != NULL)
        root = root->left;
    return root;
}

void inOrder(Node *root)
{
    if (root == NULL)
        return;
    Node *cur = leftMost(root);
    while (cur != NULL)
    {
        cout << cur->key << " ";

        if (cur->isThreaded)
        {
            cur = cur->right;
        }
        else
        {
            cur = leftMost(cur->right);
        }
    }
}

void preOrder(Node *root)
{
    if (root == NULL)
    {
        return;
    }
    Node *cur = root;
    cout << cur->key << " ";
    if (cur->left != NULL)
    {
        preOrder(cur->left);
    }
    if (cur->right != NULL && cur->isThreaded != true)
    {
        preOrder(cur->right);
    }
}
Node *newNode(int key)
{
    Node *temp = new Node;
    temp->left = temp->right = NULL;
    temp->key = key;
    return temp;
}

int main()
{
    Node *root = newNode(1);
    root->left = newNode(2);
    root->right = newNode(3);
    root->left->left = newNode(4);
    root->left->right = newNode(5);
    root->right->left = newNode(6);
    root->right->right = newNode(7);
    createThreaded(root);

    cout << "In-order traversal of created "
            "threaded tree is\n";
    inOrder(root);
    cout << "\nPre-order traversal of created "
            "threaded tree is\n";
    preOrder(root);
    return 0;
}
/*
 OUTPUT:-
 (base) kushal@kushal-Nitro-AN515-31:src$ cd "/home/kushal/eclipse-workspace/ADSL3/src/" && g++ ADSL3.cpp -o ADSL3 && "/home/kushal/eclipse-workspace/ADSL3/src/"ADSL3
In-order traversal of created threaded tree is
4 2 5 1 6 3 7 
Pre-order traversal of created threaded tree is
1 2 4 5 3 6 7 (base) kushal@kushal-Nitro-AN515-31:src$ 
*/