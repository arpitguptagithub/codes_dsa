#include <bits/stdc++.h>
#include "skiplist.h"
#define MAXI 2147.00

using namespace std;

node ::node()
{
    this->data = INT_MIN;
    this->arr.push_back(nullptr);
}

node ::node(int w)
{
    this->head = new node();
    this->head->data = INT_MIN;

    node *t = new node();
    this->head->arr.push_back(t);
    this->head->arr[0]->data = INT_MAX; // random
    this->level = 0;
}

node ::node(int data_1, node *back, int cl)
{
    node *t = new node();
    t->data = data_1;
    node *tt = back->arr[cl];
    back->arr[cl] = t;
    t->arr.push_back(tt);
}

void node::linknode(node *back, node *nl, int cl)
{
    node *t = back->arr[cl];
    back->arr[cl] = nl;
    nl->arr.push_back(t);
}

void node::insert(int data_1)
{
    int cl = this->level;
    node *cn = this->head;
    stack<node *> lns;

    while (cl >= 0)
    {
        lns.push(cn);
        while (data_1 > cn->arr[cl]->data)
        {
            cn = cn->arr[cl];
        }
        cl--;
    }
    cl = 0;

    node(data_1, cn, cl);
    cn = cn->arr[cl];

    srand(time(0));
    int random = rand();
    cl = 1;
    while (random / (double)2147483647.0 > 0.5 && lns.size() != 0)
    {
        linknode(lns.top(), cn, cl++);
        lns.pop();
    }
    level = cl;
    //    cout << level << "Check level" << endl;
}

bool node::Search(int data_1)
{
    node *cn = this->head;
    int cl = level;
    while (cl >= 0)
    {
        while (data_1 >= cn->arr[cl]->data)
        {
            cn = cn->arr[cl];
        }
        cl--;
    }
    cl++;
    cout << cn->data << "current data " << endl;
    if (data_1 == cn->data)
        return true;

    return false;
}

void node::printList()
{
    node *temp = this->head;
    while (temp->data != INT_MAX)
    {
        cout << temp->data << " ";
        temp = temp->arr[0];
    }
}

int main()
{
    node a(100);
    a.insert(5);
    a.insert(10);
    a.insert(15);
    a.printList();
    //  cout<<obj.Search(10);
    // cout<<obj.Search(20);
}