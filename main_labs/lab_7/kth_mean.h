//errors pending send to dump4+

#include <iostream> 
#include <vector> 
#include <cmath> 
#include <climits>
using namespace std;
#ifndef RBT_H
#define RBT_H
enum COLOR{RED,BLACK}; 
struct point{
    float x;
    float y;
};
struct RBNode{
    public:
    point p;
    COLOR color; 
    RBNode *left;
    RBNode *right;
    RBNode *parent;
};

RBNode* createNode(point p,RBNode* left,RBNode* right,COLOR color){
    RBNode* node=new RBNode;
    node->p=p;
    node->left=left;
    node->right=right;
    node->color=color;
    return node;
}
void LL(RBNode **H){
    RBNode *temp=(*H)->right;
    (*H)->right=temp->left;
    temp->left=*H;
    temp->color=(*H)->color;
    (*H)->color=RED;
    *H=temp;
}
void  RR(RBNode **H){
    RBNode *temp=(*H)->left;
    (*H)->left=temp->right;
    temp->right=*H;
    temp->color=(*H)->color;
    (*H)->color=RED;
    *H=temp;
}
void  LR(RBNode **H){
    RR(&(*H)->right);
    LL(H);
}
void  RL(RBNode **H){
    LL(&(*H)->left);
    RR(H);
}
void  FixUp(RBNode **H){
    if((*H)->right&&(*H)->right->color==RED&&(*H)->right->right&&(*H)->right->right->color==RED){
        if((*H)->left&&(*H)->left->color==RED){
            (*H)->color=RED;
            (*H)->left->color=BLACK;
            (*H)->right->color=BLACK;
        }
        else{
            LL(H);
        }
    }
    else if((*H)->left&&(*H)->left->color==RED&&(*H)->left->left&&(*H)->left->left->color==RED){
        if((*H)->right&&(*H)->right->color==RED){
            (*H)->color=RED;
            (*H)->left->color=BLACK;
            (*H)->right->color=BLACK;
        }
        else{
            RR(H);
        }
    }
    else if((*H)->left&&(*H)->left->color==RED&&(*H)->left->right&&(*H)->left->right->color==RED){
        RL(H);
    }
    else if((*H)->right&&(*H)->right->color==RED&&(*H)->right->left&&(*H)->right->left->color==RED){
        LR(H);
    }
}
void  FixDown(RBNode **H){
    if((*H)->left&&(*H)->left->color==RED){
        if((*H)->right&&(*H)->right->color==RED){
            (*H)->color=RED;
            (*H)->left->color=BLACK;
            (*H)->right->color=BLACK;
        }
        else if((*H)->left->left&&(*H)->left->left->color==RED){
            RR(H);
        }
        else if((*H)->left->right&&(*H)->left->right->color==RED){
            RL(H);
        }
    }
    else if((*H)->right&&(*H)->right->color==RED){
        if((*H)->right->left&&(*H)->right->left->color==RED){
            LR(H);
        }
        else if((*H)->right->right&&(*H)->right->right->color==RED){
            LL(H);
        }
    }
}
void  insert(RBNode **H,point p){
    if(*H==NULL){
        *H=createNode(p,NULL,NULL,RED);
    }
    else if(p.x<(*H)->p.x){
        insert(&(*H)->left,p);
        FixUp(H);
    }
    else if(p.x>(*H)->p.x){
        insert(&(*H)->right,p);
        FixUp(H);
    }
    else{
        if(p.y<(*H)->p.y){
            insert(&(*H)->left,p);
            FixUp(H);
        }
        else if(p.y>(*H)->p.y){
            insert(&(*H)->right,p);
            FixUp(H);
        }
    }
}
void  inorder(RBNode *H){
    if(H==NULL){
        return;
    }
    inorder(H->left);
    cout<<"("<<H->p.x<<","<<H->p.y<<")"<<endl;
    inorder(H->right);
}
void  search(RBNode *H,point p){
    if(H==NULL){
        cout<<"NOT FOUND"<<endl;
        return;
    }
    if(p.x<H->p.x){
        search(H->left,p);
    }
    else if(p.x>H->p.x){
        search(H->right,p);
    }
    else{
        if(p.y<H->p.y){
            search(H->left,p);
        }
        else if(p.y>H->p.y){
            search(H->right,p);
        }
        else{
            cout<<"FOUND"<<endl;
        }
    }
}
void deleteNode(RBNode **H,point p){
    if(*H==NULL){
        return;
    }
    if(p.x<(*H)->p.x){
        deleteNode(&(*H)->left,p);
        FixDown(H);
    }
    else if(p.x>(*H)->p.x){
        deleteNode(&(*H)->right,p);
        FixDown(H);
    }
    else{
        if(p.y<(*H)->p.y){
            deleteNode(&(*H)->left,p);
            FixDown(H);
        }
        else if(p.y>(*H)->p.y){
            deleteNode(&(*H)->right,p);
            FixDown(H);
        }
        else{
            if((*H)->left==NULL&&(*H)->right==NULL){
                delete *H;
                *H=NULL;
            }
            else if((*H)->left==NULL){
                RBNode *temp=*H;
                *H=(*H)->right;
                delete temp;
            }
            else if((*H)->right==NULL){
                RBNode *temp=*H;
                *H=(*H)->left;
                delete temp;
            }
            else{
                RBNode *temp=(*H)->right;
                while(temp->left!=NULL){
                    temp=temp->left;
                }
                (*H)->p=temp->p;
                deleteNode(&(*H)->right,temp->p);
                FixDown(H);
            }
        }
    }
}
#endif