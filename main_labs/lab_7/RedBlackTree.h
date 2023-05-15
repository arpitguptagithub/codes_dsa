
// This is the header file for the red-black tree class.  You should not

#include "points.h"

//  This is a node in the red-black tree.  It stores a Point object.
struct Node
{
    //  The Point object stored in this node.
    Point p;
    Node *left;
    Node *right;
    Node *parent;
    bool isRed;
    //  Constructor for the Node class.
    Node(Point p)
    {
        this->p = p;
        left = nullptr;
        right = nullptr;
        parent = nullptr;
        isRed = true;
    }
};

// This is a red-black tree that stores Point objects.
// The tree is ordered by the x-coordinate of the Point, and if two
// points have the same x-coordinate, then the y-coordinate is used.
class myRBTree
{ //    this->p = p;
    //    left = nullptr;
    //    right = nullptr;
    //    parent = nullptr;
    //    isRed = true;
    //  }
public:
    Node *root;
    int numNodes;
    double sumX;
    double sumY;

    myRBTree();
    void insert(Point p);
    void remove(Point p);
    void clearTree();
    Node *find(Point p);
    void print();
    void insert(Node *n);
    void remove(Node *n);
    Node *find(Node *n, Point p);
    void print(Node *n);
    void rotateLeft(Node *n);
    void rotateRight(Node *n);
    void fixInsert(Node *n);
    void fixRemove(Node *n);
    void transplant(Node *u, Node *v);
    Node *minimum(Node *n);
    Node *maximum(Node *n);
    Node *successor(Node *n);
    Node *predecessor(Node *n);
};
