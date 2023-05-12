#include <bits/stdc++.h>
using namespace std;

struct node{
    int data;
    int level;
    node* head;
    vector<node*> arr;
    void insert( int data);
    bool Search(int data);
    node (int waste);
    void printList ();
    node();
    node(int data, node*back , int cl);
    void linknode(node* back, node * nl , int cl);
};