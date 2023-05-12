#include<bits/stdc++.h>
using namespace std;

struct node{
    pair<int, int> value1;
    pair<int, int> value2;
    int height;
    node* ltree;
    node* rtree;
    bool flag_axis; // false means horizontal
  
  node(pair<int,int> value1, pair<int, int> value2 ){
    this-> value1 = value1;
    this-> value2 = value2;
    
    if(value1.first == value2.first)
     flag_axis= false;
    else
     flag_axis= true;

    ltree , rtree = NULL;
    height =1;
  }
};

int height(node * root );
node* leftrotate( node *root);
node* rightrotate(node *root);
void insert(node **root, pair<int,int> value1, pair<int,int> value2);
void deleteAVL( node** root );
int balance(node* root);
node *succesor(node *root );

struct compare{
 bool operator()( node*a , node *b )
{    return (a->value1.first < b->value1.first);
}
};

priority_queue<node*, vector<node*>, compare> vpq;

