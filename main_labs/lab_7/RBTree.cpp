#include "RedBlackTree.h"
#include <iostream>
#include <vector>

using namespace std;

myRBTree::myRBTree()
{
    root = nullptr;
    numNodes = 0;
    sumX = 0;
    sumY = 0;
}

void myRBTree::insert(Point p)
{
    Node *n = new Node(p);
    insert(n);
}

void myRBTree::insert(Node *n)
{
    Node *y = nullptr;
    Node *x = root;
    //  Find the place to insert the new node.
    while (x != nullptr)
    {
        y = x;
        if (n->p.x < x->p.x || (n->p.x == x->p.x && n->p.y < x->p.y))
            x = x->left;
        else
            x = x->right;
    }
    n->parent = y;
    //  Insert the new node.
    if (y == nullptr)
        root = n;
        //  If the new node is less than the parent, then it goes on the left.
    else if (n->p.x < y->p.x || (n->p.x == y->p.x && n->p.y < y->p.y))
        y->left = n;
        //  Otherwise, it goes on the right.
    else
        y->right = n;
    numNodes++;
    sumX += n->p.x;
    sumY += n->p.y;
    fixInsert(n);
}

void myRBTree::remove(Point p)
{
    Node *n = find(p);
    if (n != nullptr)
    {
        remove(n);
    }
}

// This is a red-black tree that stores Point objects.
void myRBTree::remove(Node *n)
{
    Node *y = n;
    Node *x;
    //  The original color of y.
    bool org_clr = y->isRed;
    //  If n only has one child, then we can just remove n and replace it with
    if (n->left == nullptr)
    {
        x = n->right;
        transplant(n, n->right);
    }
    else if (n->right == nullptr)
    {
        x = n->left;
        transplant(n, n->left);
    }
    else
    {
        y = minimum(n->right);
        org_clr = y->isRed;
        x = y->right;
        //  If y is a direct child of n, then we need to do some
        if (y->parent == n)
            x->parent = y;
        //  If y is not a direct child of n, then we need to do some
        else
        {
            transplant(y, y->right);
            y->right = n->right;
            y->right->parent = y;
        }
        transplant(n, y);
        y->left = n->left;
        y->left->parent = y;
        y->isRed = n->isRed;
    }
    //  If y's original color was black, then we need to fix the tree.
    if (!org_clr)
        fixRemove(x);
    numNodes--;
    sumX -= n->p.x;
    sumY -= n->p.y;
    delete n;
}

void myRBTree::clearTree()
{
    vector<Node *> nodes;
    //  Push the root onto the stack.
    nodes.push_back(root);
    //  While the stack is not empty, pop the top node off the stack and
    while (!nodes.empty())
    {
        Node *n = nodes.back();
        nodes.pop_back();
        if (n != nullptr)
        {
            nodes.push_back(n->left);
            nodes.push_back(n->right);
            delete n;
        }
    }
    //  Set the root to null and the number of nodes to 0.
    root = nullptr;
    numNodes = 0;
    sumX = 0;
    sumY = 0;
}

Node *myRBTree::find(Point p)
{
    return find(root, p);
}

Node *myRBTree::find(Node *n, Point p)
{
    //  If the node is null or the node's point is equal to the point we are
    if (n == nullptr || (n->p.x == p.x && n->p.y == p.y))
        return n;
    if (p.x < n->p.x || (p.x == n->p.x && p.y < n->p.y))
        return find(n->left, p);
    else
        return find(n->right, p);
}

void myRBTree::print()
{
    print(root);
}

void myRBTree::print(Node *n)
{
    if (n == nullptr)
        return;
    print(n->left);
    cout << "(" << n->p.x << ", " << n->p.y << ") ";
    print(n->right);
}

void myRBTree::rotateLeft(Node *n)
{
    //  y is the right child of n.
    Node *y = n->right;
    n->right = y->left;
    //  If y has a left child, then we need to set its parent to n.
    if (y->left != nullptr)
        y->left->parent = n;
    y->parent = n->parent;
    //  If n is the root, then we need to set the root to y.    
    if (n->parent == nullptr)
        root = y;
    //  If n is the left child of its parent, then we need to set the parent's
    else if (n == n->parent->left)
        n->parent->left = y;
    //  Otherwise, we need to set the parent's right child to y.
    else
        n->parent->right = y;
    y->left = n;
    n->parent = y;
}


//  This function rotates the tree to the right.
void myRBTree::rotateRight(Node *n)
{
    Node *y = n->left;
    n->left = y->right;
    if (y->right != nullptr)
        y->right->parent = n;
    y->parent = n->parent;
    if (n->parent == nullptr)
        root = y;
    else if (n == n->parent->right)
        n->parent->right = y;
    else
        n->parent->left = y;
    y->right = n;
    n->parent = y;
}

//  This function fixes the tree after an insertion.
void myRBTree::fixInsert(Node *n)
{ //  While n is not the root and n's parent is red.
    while (n != root && n->parent->isRed)
    {
        if (n->parent == n->parent->parent->left)
        {
            Node *y = n->parent->parent->right;
            //  If y is red, then we need to recolor.
            if (y != nullptr && y->isRed)
            {
                n->parent->isRed = false;
                y->isRed = false;
                n->parent->parent->isRed = true;
                n = n->parent->parent;
            }
            // if y is black, then we need to rotate.
            else
            {
                if (n == n->parent->right)
                {
                    n = n->parent;
                    rotateLeft(n);
                }
                n->parent->isRed = false;
                n->parent->parent->isRed = true;
                rotateRight(n->parent->parent);
            }
        }
        //  If n's parent is the right child of its parent.
        else
        {
            Node *y = n->parent->parent->left;
            //  If y is red, then we need to recolor.
            if (y != nullptr && y->isRed)
            {
                n->parent->isRed = false;
                y->isRed = false;
                n->parent->parent->isRed = true;
                n = n->parent->parent;
            }
            //  If y is black, then we need to rotate.
            else
            {
                //  If n is the left child of its parent, then we need to rotate
                if (n == n->parent->left)
                {
                    n = n->parent;
                    rotateRight(n);
                }
                n->parent->isRed = false;
                n->parent->parent->isRed = true;
                rotateLeft(n->parent->parent);
            }
        }
    }
    root->isRed = false;
}

void myRBTree::fixRemove(Node *n)
{
    //  While n is not the root and n is black.
    while (n != root && !n->isRed)
    { //  If n is the left child of its parent.
        if (n == n->parent->left)
        {
            //  Set w to n's sibling.
            Node *w = n->parent->right;
            if (w->isRed)
            {
                w->isRed = false;
                n->parent->isRed = true;
                rotateLeft(n->parent);
                w = n->parent->right;
            }
            //  If w's children are black, then we need to recolor.
            if (!w->left->isRed && !w->right->isRed)
            {
                w->isRed = true;
                n = n->parent;
            }
            //  If w's right child is black, then we need to recolor and rotate.
            else
            {
                if (!w->right->isRed)
                {
                    w->left->isRed = false;
                    w->isRed = true;
                    rotateRight(w);
                    w = n->parent->right;
                }
                w->isRed = n->parent->isRed;
                n->parent->isRed = false;
                w->right->isRed = false;
                rotateLeft(n->parent);
                n = root;
            }
        }
        //  If n is the right child of its parent.
        else
        {
            Node *w = n->parent->left;
            if (w->isRed)
            {
                w->isRed = false;
                n->parent->isRed = true;
                rotateRight(n->parent);
                w = n->parent->left;
            }
            //  If w's children are black, then we need to recolor.
            if (!w->right->isRed && !w->left->isRed)
            {
                w->isRed = true;
                n = n->parent;
            }
            //  If w's left child is black, then we need to recolor and rotate.
            else
            {
                if (!w->left->isRed)
                {
                    w->right->isRed = false;
                    w->isRed = true;
                    rotateLeft(w);
                    w = n->parent->left;
                }
                w->isRed = n->parent->isRed;
                n->parent->isRed = false;
                w->left->isRed = false;
                rotateRight(n->parent);
                n = root;
            }
        }
    }
    //  Set n to black.
    n->isRed = false;
}

//  This function inserts a node into the tree.
//  It takes a pointer to the root of the tree and a pointer to the node to be inserted.
//  It returns a pointer to the root of the tree.
//  This function is called by the public insert function.

void myRBTree::transplant(Node *u, Node *v)
{
    //  If u is the root, then v becomes the root.  
    if (u->parent == nullptr)
        root = v;
    else if (u == u->parent->left)
        u->parent->left = v;
    else
        u->parent->right = v;
        //  If v is not null, then v's parent is u's parent.
    if (v != nullptr)
        v->parent = u->parent;
}

//  This functiion point to the node to find minimum value.
Node *myRBTree::minimum(Node *n)
{
    while (n->left != nullptr)
        n = n->left;
    return n;
}

//this function point to the node to find maximum value.
Node *myRBTree::maximum(Node *n)
{
    while (n->right != nullptr)
        n = n->right;
    return n;
}
//  This function finds the successor of a node.

Node *myRBTree::successor(Node *n)
{
    //  If n has a right child, then the successor is the minimum value in the right subtree.
    if (n->right != nullptr)
        return minimum(n->right);
    Node *y = n->parent;
    //  If n does not have a right child, then the successor is the lowest ancestor of n whose left child is also an ancestor of n.
    while (y != nullptr && n == y->right)
    {
        n = y;
        y = y->parent;
    }
    return y;
}

Node *myRBTree::predecessor(Node *n)
{
    //  If n has a left child, then the predecessor is the maximum value in the left subtree.
    if (n->left != nullptr)
        return maximum(n->left);
    Node *y = n->parent;
    while (y != nullptr && n == y->left)
    {
        n = y;
        y = y->parent;
    }
    return y;
}