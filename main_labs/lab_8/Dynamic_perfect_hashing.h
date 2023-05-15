#include <bits/stdc++.h>
using namespace std; 
int counter = 0; //counter for the number of elements in the hash table
long long int p = 1e9 + 7; //prime number
int m = 10; //size of the hash table
#define acc table[index]->sub_table
struct Node //node of the hash table
{
    vector<pair<int, bool>> sub_table; // 1 - deleted, 0 - alive
    int sub_count;

    Node()
    {
        sub_count = 0;//number of elements in the sub table
    }
};

class HashMap // 
{
public:
    int count = 0;
    // bool markDeleted;
    vector<Node *> table;
    void Insert(); //inserts the element in the hash table
    void rehashall(vector<int> sub_table); //rehashes the whole table
    int MappingFunction(int key, int t_ele); //hash function
    void Insert(int key); //inserts the element in the hash table
    int find_element(vector<Node *> table, int index, int sub_index, int key); //finds the element in the hash table
    void rehash_subtable(vector<int> temp, int index); //rehashes the sub table
    void delete_element(int x);
    HashMap(); //constructor
   //deleting the node 
};
