#include "Dynamic_perfect_hashing.h"


int HashMap::MappingFunction(int key, int t_ele)
{
   int a = 102112;
   int b = 1212222121;

    int val = (( a* key + b) % p) % t_ele; // hash function
    return val;
}

int HashMap::find_element(vector<Node *> table, int index, int sub_index, int key)
{

    if (table[index]->sub_table[sub_index].first == key)
        return 1; // element found

    return -1;
}

void HashMap::rehash_subtable(vector<int> temp, int index)
{
    int size = table[index]->sub_table.size(); //
    bool status = true;
    while (status) // rehashing the sub table until no collision occurs
    {
        status = false;
        table[index]->sub_table.clear();
        table[index]->sub_table.resize(size); // resizing the sub table
        for (int i = 0; i < size; i++)
        {
            acc[i].first = INT_MAX;
        }
        for (int i : temp) // rehashing elements
        {
            int sub_index = MappingFunction(i, size);
            if (acc[sub_index].first == INT_MAX) // if no collision occurs
            {
                acc[sub_index] = {i, 0};
            }
            else // collision
            {
                status = true;
                break;
            }
        }
    }
}

HashMap::HashMap()
{
    this->table.resize(m);
    for (int i = 0; i < m; i++) // creating new nodes
    {
        table[i] = new Node();
    }
}

void HashMap::Insert(int x)
{
    count++;
    if (count > m) // if the number of elements in the hash table exceeds the size of the hash table
    {
        vector<int> temp_list;
        for (Node *i : table) // traversing the hash table
        {
            for (pair<int, bool> j : i->sub_table)
            {
                if (j.second == 0) // if the element is not deleted
                {
                    temp_list.push_back(j.first); // pushing the element in the temp list
                }
            }
        }
        int n = temp_list.size();

        table.erase(table.begin(), table.end()); // clearing the hash table
        table.resize(2 * n);
        m = 2 * n; // doubling size for the main table
        for (int i = 0; i < 2 * n; i++)
        {
            table[i] = new Node(); // creating new nodes
        }
        count = 0;
        rehashall(temp_list); // rehashing the whole table
        Insert(x);
    }
    else
    {
        int j = MappingFunction(x, m); // hashing the element
        if (!table[j]->sub_table.size())
        {
            table[j]->sub_table.resize(1); // resizing the sub table
            table[j]->sub_table[0].first = INT_MAX;
        }
        int subindex = MappingFunction(x, table[j]->sub_table.size());
        // int bucket_index = find_element(table, j, sub_index, x);
        if (find_element(table, j, subindex, x) != -1)
        {
            if (table[j]->sub_table[subindex].second == 1) // if delete operation on element
            {
                table[j]->sub_table[subindex].second == 0; // marking the element as alive
            }
        }
        else
        {
            table[j]->sub_count++;                                 // incrementing the number of elements in the sub table
            if (table[j]->sub_count <= table[j]->sub_table.size()) // if the number of elements in the sub table is less than the size of the sub table
            {
                if (table[j]->sub_table[subindex].first == INT_MAX) // if the sub table is empty
                {
                    table[j]->sub_table[subindex] = {x, 0};
                }
                else
                {
                    vector<int> temp(table[j]->sub_count);
                    for (pair<int, bool> i : table[j]->sub_table) // pushing the elements in the temp list
                    {
                        if (i.second == 0)
                            temp.push_back(i.first); // pushing the element in the temp list
                    }
                    temp.push_back(x);        // pushing the new element in the temp list
                    rehash_subtable(temp, j); // rehashing the sub table
                }
            }
            else
            {
                int total_subsize = pow(table[j]->sub_table.size(), 2); // calculating the total size of the sub table
                for (Node *i : table)
                {
                    total_subsize += i->sub_table.size(); // calculating the total size of the hash table
                }
                total_subsize -= table[j]->sub_table.size();

                if (total_subsize > 4 * count) // c (constant) = 4 //if the total size of the hash table is greater than 4 times the number of elements in the hash table
                {
                    vector<int> temp_list;
                    for (Node *i : table)
                    {
                        for (pair<int, bool> j : i->sub_table) // pushing the elements in the temp list
                        {
                            if (j.second == 0)
                            {
                                temp_list.push_back(j.first);
                            }
                        }
                    }
                    int n = temp_list.size();

                    // double alpha = (double)n / m;
                    // double c = 4;
                    // int new_m = 1 + c * max(n, 4);
                    table.erase(table.begin(), table.end()); // clearing the hash table
                    table.resize(n);
                    for (int i = 0; i < n; i++) // creating new nodes
                    {
                        table[i] = new Node();
                    }
                    count = 0;
                    rehashall(temp_list); // rehashing the whole table
                    Insert(x);
                }
                else
                {
                    vector<int> temp(table[j]->sub_count); // creating a temp list
                    for (pair<int, bool> i : table[j]->sub_table)
                    {
                        if (i.second == 0) // pushing the elements in the temp list
                            temp.push_back(i.first);
                    }
                    temp.push_back(x); // pushing the new element in the temp list

                    table[j]->sub_table.erase(table[j]->sub_table.begin(), table[j]->sub_table.end()); // clearing the sub table
                    table[j]->sub_table.resize(pow(temp.size(), 2));                                   // resizing the sub table
                    rehash_subtable(temp, j);                                                          // rehashing the sub table
                }
            }
        }
    }
}



void HashMap::rehashall(vector<int> list)
{
    for (int i : list)
    {
        Insert(i);
    }
}









void HashMap::delete_element(int x)
{
//counting for the size 
   cout<<"table size" <<table.size() <<endl;
    int index = MappingFunction(x, table.size());
        count++; 

        cout<<"index"<<index<<endl;
        cout <<table[index]->sub_table.size()<<endl;



        int subindex = MappingFunction(x, table[index]->sub_table.size());
        // int bucket_index = find_element(table, j, sub_index, x);
        if (find_element(table, index, subindex, x) == 1)
        {
           table[index ]->sub_table[subindex].second = 1; 
             count++;
        }

        if (count >= m) //rehashing again if table size is smaller than a threshold 
         { vector<int>temp;
               temp.push_back(table[index]->sub_table[subindex].first);
                 rehashall( temp);
        }

}















    //     int sub_index = find_element(table, index,0, x);
    //     if (sub_index != -1)
    //     {
    //         if (table[index]->sub_table[sub_index].second == 0)
    //         {
    //             table[index]->sub_table[sub_index].second = 1;
    //             count--;
    //         }
    //     }
    // }












//cout<<index<<"index"; // j <-h(x)
    // for (int i = 0; i < table[index ]->sub_table.size(); i++)
    // {
    //     if (table[index]->sub_table[i].first == x)  //checking if it contains x 
    //     {
    //         table[index ]->sub_table[i].second = 1; 
    //          cout<<endl;
    //          cout<<x;

    //          // marking deleted 
    //         //  count--;
    //         if (count >= m) //rehashing again if table size is smaller than a threshold 
    //         { vector<int>temp;
    //           temp.push_back(table[index]->sub_table[i].first);
    //             rehashall( temp);
    //         }

    //         break;
    //     }
    // }



















// void HashMap::rehashall(int x)
// {
//     int n = count;
//     double alpha = (double)n / m;
//     double c = 4;
//     int new_m = 1 + c * max(n, 4);
//     while (s(new_m) < 2 * alpha)
//     {
//         new_m++;
//     }
//     int new_M = (int)ceil((double)n / new_m);

//     vector<Node *> H1(new_M);
//     for (int i = 0; i < new_M; i++)
//     {
//         H1[i] = new Node();
//     }

//     vector<vector<int>> temp(new_M);
//     for (int i = 0; i < table.size(); i++)
//     {
//         if (table[i] != nullptr)
//         {
//             for (int j = 0; j < acc.size(); j++)
//             {
//                 if (acc[j].second == false)
//                 {
//                     temp[MappingFunction(acc[j].first, new_M)].push_back(acc[j].first);
//                 }
//             }
//         }
//     }

//     for (int i = 0; i < table.size(); i++)
//     {
//         if (table[i] != nullptr)
//         {
//             for (int j = 0; j < acc.size(); j++)
//             {
//                 if (acc[j].second == false)
//                 {
//                     int index = MappingFunction(acc[j].first, new_M);
//                     int sub_index = find_element(H1, index, acc[j].first);
//                     H1[index]->sub_table[sub_index] = {acc[j].first, false};
//                 }
//             }
//             delete table[i];
//         }
//     }
//     table = H1;
//     m = new_m;
// }