#include "intersectionLine.h"

int height(node *root)
{
  if (root == NULL)
    return 0;
  return root->height;
}

node *rightrotate(node *root)
{
  node *x = root->ltree;
  node *y = root->rtree;

  x->rtree = root;
  root->ltree = y;

  root->height = max(height(root->ltree), height(root->rtree)) + 1;
  x->height = max(height(x->ltree), height(x->rtree)) + 1;

  return x;
}

node *leftrotate(node *x)
{
  node *y = x->rtree;
  node *T2 = y->ltree;

  y->ltree = x;
  x->rtree = T2;

  x->height = max(height(x->ltree),
                  height(x->rtree)) +
              1;
  y->height = max(height(y->ltree),
                  height(y->rtree)) +
              1;

  return y;
}

int balance(node *root)
{
  if (root == NULL)
    return 0;
  return height(root->ltree) - height(root->rtree);
}

node *succesor(node *root)
{
  if (root->ltree == NULL)
    return root;
  return succesor(root->ltree);
}





void insert(node **root, pair<int, int> value1, pair<int, int> value2)
{
  if ((*root) == NULL)
  {
    *root=new node(value1, value2);
    return;
  }

  else if (value1.first < (*root)->value1.first)
  {
    insert(&((*root)->ltree), value1, value2);
  }
  else
  {
    insert(&((*root)->rtree), value1, value2);
  }

  (*root)->height = 1 + max(height((*root)->ltree),
                            height((*root)->rtree));

  int bln = balance((*root));

  if (bln > 1 && value1.first < (*root)->ltree->value1.first)
    rightrotate(*root);

  if (bln < -1 && value1.first > (*root)->rtree->value1.first)
    leftrotate(*root);

  if (bln > 1 && value1.first > (*root)->ltree->value1.first)
  {
    (*root)->ltree = leftrotate((*root)->ltree);
    rightrotate((*root));
  }

  if (bln < -1 && balance((*root)->rtree)>0)
  {
    (*root)->rtree = rightrotate((*root)->rtree);
    leftrotate(*root);
  }

  return;
}

void insert( node *r)
{
  insert( &root, r->value1, r->value2 ) 
}

void deleteAVL(node **root, pair<int, int> value1, pair<int, int> value2)
{
  if (*(root) == NULL)
    return ;

  if (value1.first < (*root)->value1.first)
    deleteAVL(&(*root)->ltree, value1, value2);

  else if (value1.first > (*root)->value1.first)
    deleteAVL(&(*root)->rtree, value1, value2);

  else
  {

    if ((*root)->ltree == NULL || (*root)->rtree == NULL)
    {
      node *temp = (*root)->ltree ? (*root)->ltree : (*root)->rtree;

      if (temp == NULL)
      {
        temp = (*root);
        root = NULL;
      }

      else
        *(*root) = *temp;

      free(temp);
    }

    else
    {

      node *temp = succesor((*root)->rtree);
      (*root)->value1.first = temp->value1.first;
       deleteAVL(&((*root)-> rtree), value1, value2);
    }
  }

  if ((*root) == NULL)
    return ;

  (*root)->height = 1 + max(height((*root)->ltree), height((*root)->rtree));

  int bln = balance((*root));

  if (bln > 1 && value1.first < (*root)->ltree->value1.first)
     rightrotate(*root);

  if (bln < -1 && value1.first > (*root)->rtree->value1.first)
     leftrotate(*root);

  if (bln > 1 && value1.first > (*root)->ltree->value1.first)
  {
    (*root)->ltree = leftrotate((*root)->ltree);
     rightrotate((*root));
  }

  if (bln < -1 && value1.first < (*root)->rtree->value1.first)
  {
    (*root)->rtree = rightrotate((*root)->rtree);
     leftrotate(*root);
  }

   *root;
}

void inorder( node *root)
{
  if (  root == NULL)
    return;

  inorder( root->ltree);
  cout << root->value1.first;
  inorder( root->rtree);


}

void checkIntersection (node* root , pair<int,int> value1 , pair<int, int> value2 )
{
 if (root == NULL)
 {
   return;
 }
checkIntersection( root->ltree, value1, value2);

if( root->value1.first <= value1.first &&
    root->value2.first >= value1.first &&
    root->value1.second <= value1.second  &&
    root->value2.second >= value2.second)
{
 cout << value1.first << root->value1.second;
 return ;
}



// cout << value1.first << value1.second;
// cout << value2.first << value2.second;

// cout << root->value1.first << root->value1.second;
// cout << root->value2.first << root->value2.second;


checkIntersection( root->rtree, value1, value2);

}
void checkInsertion( node* r)
{
  checkIntersection(&root, r->value1 , r->value2);
}
//

int main()
{
  priority_queue<node*, vector<node*>, compare> vpq;
   int n, x, y, x1, y1,axis;
 
  cin>>n;
  for(int i =0 ; i<n ; i++)
   {
    cin>>x>>y >>x1 >>y1>>axis;
     
       node* root =new node({x,y},{x1,y1});
    if( axis== 0)
    { vpq.push(root);}

   }

    node* root =new node({x,y},{x1,y1});
  
   priority_queue<node*, vector<node*>, compare> pq;
 while (!vpq.empty())
 {
   node *n = vpq.top();
    vpq. pop(); 
    if (n->flag_axis == 0)
      root.insert(&n) //
    else 
      pq.push(n)
 }

 while (!pq.empty())
 {
   node *n =pq.top();
   pq.pop();
   root.checkIntersection(&n); 
 }

 return 0;
//  cout<<"hehe";
//   insert(&root, {10, 20}, {10, 56});
//   insert(&root, {20, 20}, {20, 56});
//    insert(&root, {30, 20}, {30, 56});
//    inorder ( root );

//    deleteAVL ( &root , {30,26}, {30,56});
}
