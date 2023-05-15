#include <bits/stdc++.h>
using namespace std;


//  defined a seperate structure for the point
struct point
{
    int x;
    int y;
    point(int x1, int y1) : x(x1), y(y1) {}
};

//taking the line as another datatype
struct l_segment
{
    point first_point;
    point Second_point;
    bool axis; // v =1 
    l_segment(point p1, point p2, bool p) : first_point(p1), Second_point(p2), axis(p) {}
};


//comparator for the priority queue
struct Comparex
{//comparator for the priority queue
    bool operator()(l_segment const &p1, l_segment const &p2)
    {
        return p1.first_point.x > p2.first_point.x;
    }
};


//class for defining the avl tree
class AVLTree
{
    struct Node
    {
        
        l_segment p;
        Node *left;
        Node *right;
        int height;
        //consttruvtor for the node
        Node(l_segment pp) : p(pp), left(NULL), right(NULL), height(1) {}
    };
    Node *root;

//function for the height of the node
    int height(Node *node)
    {
        if (node == NULL)
        {
            return 0;
        }
        return node->height;
    }
//function for the height difference
    int heightdiff(Node *node)
    {
        if (node == NULL)
        {
            return 0;
        }
        return height(node->left) - height(node->right);
    }
//rotation functions
    void R_left(Node *&node)
    {
        Node *temp = node->right;
        node->right = temp->left;
        temp->left = node;
        node->height = max(height(node->left), height(node->right)) + 1;
        temp->height = max(height(temp->left), height(temp->right)) + 1;
        node = temp;
    }
//rotate right
    void R_right(Node *&node)
    {
        Node *temp = node->left;
        node->left = temp->right;
        temp->right = node;
        node->height = max(height(node->left), height(node->right)) + 1;
        temp->height = max(height(temp->left), height(temp->right)) + 1;
        node = temp;
    }
//balancing the tree
    void balance(Node *&node)
    {
       // cout << "balancing" << endl;
        int bf = heightdiff(node);
        //cout << bf << endl;

        if (bf > 1)
        { // this means that the left subtree is heavier
            if (heightdiff(node->left) < 0)
            {
                R_left(node->left);
            }
            R_right(node);
        }
        else if (bf < -1)
        { // this means that the right subtree is heavier
            if (heightdiff(node->right) > 0)
            {
                R_right(node->right);
            }
            R_left(node);
        }
    }
    // insertion in avl tree
    void insert(Node *&node, l_segment p)
    {
        if (node == NULL)
        {
            node = new Node(p);
            return;
        }
        if (p.first_point.x < node->p.first_point.x)
        {
            insert(node->left, p);
        }
        else
        {
            insert(node->right, p);
        }
        node->height = max(height(node->left), height(node->right)) + 1;
        balance(node);
    }
//constructor
public:
    AVLTree() : root(NULL) {}

    void insert(l_segment p)
    {
        insert(root, p);
    }

    void inorder(Node *node)
    {
        if (node == NULL)
        {
            return;
        }
        inorder(node->left);
        cout << "(" << node->p.first_point.x << ", " << node->p.first_point.y << ")" << endl;
        inorder(node->right);
    }

    void inorder()
    {
        inorder(root);
    }

//     ~AVLTree()
//     {
//         deleteTree(root);
//     }
// //according to the question we are required to follow level order traversal
    void levelOrder(Node *root)
    {
        queue<Node *> q;
        q.push(root);

        while (!q.empty())
        {
            root = q.front();
            std::cout << root->p.first_point.x << " " << root->p.first_point.y << std::endl;
            q.pop();
            if (root->left)
            {
                q.push(root->left);
            }
            // 
            if (root->right)
            {
                q.push(root->right);
            }
        }
    }


//code for the level order traversal
    void levelOrder()
    {
        levelOrder(root);
    }
};