

#include <iostream>
#include <vector>
#include <set>
#include <algorithm>
#include <queue>

using namespace std;

// struct to represent vertical and horizontal lines
struct VerticalLine {
    int x, y1, y2;
};

struct HorizontalLine {
    int y, x1, x2;
};

// struct to represent a node in the AVL tree
struct Node {
    HorizontalLine line;
    int height;
    Node* left;
    Node* right;
};

// function to calculate the height of a node
int height(Node* node) {
    return node == nullptr ? -1 : node->height;
}

// function to calculate the balance factor of a node
int balanceFactor(Node* node) {
    return node == nullptr ? 0 : height(node->left) - height(node->right);
}

// function to rotate a subtree to the left
Node* rotateLeft(Node* node) {
    Node* newRoot = node->right;
    node->right = newRoot->left;
    newRoot->left = node;
    node->height = max(height(node->left), height(node->right)) + 1;
    newRoot->height = max(height(newRoot->left), height(newRoot->right)) + 1;
    return newRoot;
}

// function to rotate a subtree to the right
Node* rotateRight(Node* node) {
    Node* newRoot = node->left;
    node->left = newRoot->right;
    newRoot->right = node;
    node->height = max(height(node->left), height(node->right)) + 1;
    newRoot->height = max(height(newRoot->left), height(newRoot->right)) + 1;
    return newRoot;
}

// function to balance a node
Node* balance(Node* node) {
    int bf = balanceFactor(node);
    if (bf > 1) {
        if (balanceFactor(node->left) < 0) {
            node->left = rotateLeft(node->left);
        }
        node = rotateRight(node);
    } else if (bf < -1) {
        if (balanceFactor(node->right) > 0) {
            node->right = rotateRight(node->right);
        }
        node = rotateLeft(node);
    }
    return node;
}

// function to insert a horizontal line into the AVL tree
Node* insert(Node* root, const HorizontalLine& line) {
    if (root == nullptr) {
        root = new Node{line, 0, nullptr, nullptr};
    } else if (line.y < root->line.y) {
        root->left = insert(root->left, line);
    } else {
        root->right = insert(root->right, line);
    }
    root->height = max(height(root->left), height(root->right)) + 1;
    return balance(root);
}

// function to delete a horizontal line from the AVL tree
Node* deleteLine(Node* root, const HorizontalLine& line) {
    if (root == nullptr) {
        return nullptr;
    } else if (line.y < root->line.y) {
        root->left = deleteLine(root->left, line);
    } else if (line.y > root->line.y) {
        root->right = deleteLine(root->right, line);
    } else {
        if (root->left == nullptr && root->right == nullptr) {
            delete root;
            return nullptr;
        } else if (root->left == nullptr) {
            Node* temp = root->right;
            delete root;
            return temp;
        } else if (root->right == nullptr) {
            Node* temp = root->left;
            delete root;
            return temp;
        } else {
            Node* temp = root->right;
            while (temp->left != nullptr) {
                temp = temp->left;
            }
            root->line = temp->line;
            root->right = deleteLine(root->right, temp->line);
        }
    }
    root->height = max(height(root->left), height(root->right)) + 1;
    return balance(root);
}


class compare {
public:
    bool operator()(const VerticalLine& a, const VerticalLine& b) {
        return a.x < b.x;
    }
};

// Define the AVL tree
Node* activeLines = nullptr;

// Define the line sweep algorithm using an AVL tree
set<pair<int, int>> findIntersections(priority_queue<VerticalLine, vector<VerticalLine>, compare>& verticalLines, vector<HorizontalLine>& horizontalLines) {
    set<pair<int, int>> intersections;
    sort(horizontalLines.begin(), horizontalLines.end(), [](const HorizontalLine& a, const HorizontalLine& b) {
        return a.y < b.y;
    });
    int i = 0;
    while (!verticalLines.empty()) {
        VerticalLine line = verticalLines.top();
        verticalLines.pop();
        while (i < horizontalLines.size() && horizontalLines[i].y <= line.y2) {
            activeLines = insert(activeLines, horizontalLines[i]);
            i++;
        }
        Node* temp = activeLines;
        while (temp != nullptr) {
            if (temp->line.x1 <= line.x && temp->line.x2 >= line.x) {
                intersections.insert({line.x, temp->line.y});
            }
            temp = temp->right;
        }
        activeLines = deleteLine(activeLines, {line.y1, line.x, line.x});
    }
    return intersections;
}


// Example usage:
int main() {
    //store vertical lines in priorty queue
    priority_queue <VerticalLine, vector<VerticalLine>, compare> verticalLines;
    verticalLines.push({4, 0, 8});
    verticalLines.push({3, 4, 0});
    vector<HorizontalLine> horizontalLines = {{2, -3, 9}, {1, -3, 9}};  // y, x1, x2
    
    set<pair<int, int>> intersections = findIntersections(verticalLines, horizontalLines);
    cout << "Intersections:" << endl;
    for (const auto& p : intersections) {
        cout << "(" << p.first << ", " << p.second << ")" << endl;
    }
    return 0;
}



