
#include "Dynamic_perfect_hashing.cpp"

using namespace std;
int main()
{

    HashMap *obj = new HashMap();
    bool status = true;
    while (status)
    { //0 for no input required and 1 for input required
        cout << "Insert Elemenet " << endl;
        int choice = 0;
        cin >> choice;
        if (choice == 0)
        {
            status = false;
            cout<<endl;
        }
        //enter the element
        else
        {
            cout << "Input : " << endl;
            int num;
            cin >> num;
            obj->Insert(num);
        }
    }
    cout<<endl;

   
    for (int i = 0; i < m; i++)
    {//printing the hash table
        for (pair<int, bool> j : obj->table[i]->sub_table)
        {
            if (j.first != INT_MAX)
                cout << j.first <<"  index  "<<i << " "<<endl;
        }
        cout<< "size"<< obj->table[i]->sub_table.size() <<endl;

        
    }

    cout << "Enter the element to be deleted" << endl;
    int x;
    cin>>x;
     obj->delete_element(x);

   

        for (int i = 0; i < m; i++)
    {//printing the hash table
        for (pair<int, bool> j : obj->table[i]->sub_table)
        {
            if (j.first != INT_MAX && j.second == 0)
                cout << j.first <<" " <<j.second<< endl;
        }
    }
}