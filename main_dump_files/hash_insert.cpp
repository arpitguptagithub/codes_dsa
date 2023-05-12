#include<bits/stdc++.h> 
using namespace std;

#define m 200 //size of table
#define pn 14071 //just a big prime number // require more big
#define aran 100 //random number
#define bran 200 //random number 

unsigned long hfunc( char * str)
{
    unsigned long i =0 ;
    for ( int j =0; j< str[j] ; j ++)
     i += str[j];

return (((aran)*i + bran )% pn) %m;
}


struct ht_item {
    char * key;
    char * value;
   
};

ht_item * create_item ( char * key , char* value)
{
    ht_item* item = (ht_item*) malloc( sizeof(ht_item));
    item->key = (char*) malloc(strlen(key) +1);
    item->value = (char*) malloc(strlen(value) + 1);
    strcpy(item->key, key);
    strcpy(item->value, value);
    return item;

}

struct ht_table {
    ht_item** items;
    int capacity;
    int count; 
    
};

ht_table* create_table ( int size )
{
    ht_table * table = (ht_table*) malloc( sizeof(ht_table) );
    table->capacity = size;
    table->count = 0;
    table->items = (ht_item**) calloc(table->capacity, sizeof(ht_item*));

    for (int i = 0; i < table->capacity; i++)
        table->items[i] = NULL;

    return table;
 }


 ht_table* rehashAll (ht_table* table, ht_item * item )
 {
  return table ;
 }

void free_item(ht_item* item)
{
    // Frees an item.
    free(item->key); 
    free(item->value);
    free(item);
}

void free_table(ht_table* table)
{
    for (int i = 0; i < table->capacity; i++)
    {
        ht_item* item = table->items[i];

        if (item != NULL)
            free_item(item);
    }

    free(table->items);
    free(table);
}



void print_table(ht_table* table)
{
 for (int i = 0; i < table->capacity; i++)
    {
        if (table->items[i])
        {
            cout<< i << " "<< table->items[i] -> key<<" "<< table->items[i]->value;
        }
    }

}

void ht_insert ( ht_table* table, char* key , char *value)
{
 ht_item * item = create_item( key, value);


 table->count++;
 if ( table->count> m)

  rehashAll( table, item);
else 
{
  int index = hfunc(key);
  if (table->items[index] )
    {
        free_item(table->items[index]);
        table->items[index] = item;
    }
    else
    {
        table->items[index] = item;
    }
}
}

