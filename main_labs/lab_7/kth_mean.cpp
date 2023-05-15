//errors pending send to dump4+



#include <bits/stdc++.h>
#include "kth_mean.h"

using namespace std;

float dist(point a,point b){
    return sqrt((a.x-b.x)*(a.x-b.x)+ (a.y-b.y)*(a.y-b.y));
}
pair<int,pair<float,float>> centroid(RBNode *H){
    if(H==NULL){return {0,{0,0}};}
    pair<int,pair<float,float>> left=centroid(H->left);
    pair<int,pair<float,float>> right=centroid(H->right);
    int count=left.first+right.first+1;
    float x=(left.second.first*left.first+right.second.first*right.first+H->p.x)/count;
    float y=(left.second.second*left.first+right.second.second*right.first+H->p.y)/count;
    return {count,{x,y}};
}
pair<bool,int> is_in_group(point p,pair<pair<float,float>,RBNode*> Groups[],int k,int curr_grp_num){
    //if p has least siatance only to its current group then it is in its group
    float min_dist=INT_MAX;
    int min_index=-1;
    for(int i=0;i<k;i++){
        float temp=dist(p,{Groups[i].first.first,Groups[i].first.second});
        if(temp<min_dist){
            min_dist=temp;
            min_index=i;
        }
    }
    if(min_index==curr_grp_num){return {true,curr_grp_num};}
    return {false,min_index};
}

//if p is not in its group then remove it from its group and insert it in the group of min_index
void rearrange_point(bool& changedFlag,RBNode *H,point p,pair<pair<float,float>,RBNode*>* Groups[],int k,int curr_grp_num){
    pair<bool,int> temp=is_in_group(p,Groups,k,curr_grp_num);
    if(temp.first==true){return;}
    changedFlag=true;
    //deleteNode p from its group(curr_grp_num) and insert it in the group of min_index(temp.second)
    deleteNode(H,p);
    insert(&Groups[temp.second].second,p);
}

//REARRANGE FOR RECURSIVE CALL ON GROUPS
void rearrange_group(bool& changedFlag,RBNode *H,pair<pair<float,float>,RBNode> Groups[],int k,int curr_grp_num){
    if(*H == NULL){return;}
    rearrange_group(changedFlag,&(*H)->left,Groups,k,curr_grp_num);
    rearrange_point(changedFlag,H,(*H)->p,Groups,k,curr_grp_num);
    rearrange_group(changedFlag,&(*H)->right,Groups,k,curr_grp_num);
}

void rearrange(bool& changedFlag,pair<pair<float,float>,RBNode*> Groups[],int k){
    for(int i=0;i<k;i++){rearrange_group(changedFlag,&Groups[i].second,Groups,k,i);}
}
void centroid_recalc(int k,pair<pair<float,float>,RBNode*> Groups[]){ 
    for(int i=0;i<k;i++){
        pair<int,pair<float,float>> temp=centroid(Groups[i].second);
        Groups[i].first.first=temp.second.first;
        Groups[i].first.second=temp.second.second;
    }
}
void print(RBNode *H){
    if(H==NULL){return;}
    print(H->left);
    cout<<"("<<H->p.x<<","<<H->p.y<<") ";
    print(H->right);
}
void printk(int k,pair<pair<float,float>,RBNode*> Groups[]){
    cout<<"print start:\n ************"<<endl;
    for(int i=0;i<k;i++){
        cout<<"Group "<<i<<":****\n";
        cout<<"Centroid: "<<Groups[i].first.first<<" "<<Groups[i].first.second<<endl;
        cout<<"Points: ";
        print(Groups[i].second);
        cout<<endl;        
    }
}
int main(){
    srand(abs(time(0)));
    int n;
    cout<<"Enter the number of points: ";
    cin>>n;
    vector<point> points(n);
    for(int i=0;i<n;i++){
        points[i].x=rand()%1000;
        points[i].y=rand()%1000;
    }
    int k;
    cout<<"Enter the number of clusters: ";
    cin>>k;
    pair<pair<float,float>,RBNode*> Groups[k];
    for(int i=0;i<k;i++){
        Groups[i].first.first=points[i].x;
        Groups[i].first.second=points[i].y;
        Groups[i].second=NULL;
    }
    //first phase
    for(int i=0;i<n;i++){
        float min_dist=INT_MAX;
        int min_index=-1;
        for(int j=0;j<k;j++){
            float temp=dist(points[i],{Groups[j].first.first,Groups[j].first.second});
            if(temp<min_dist){
                min_dist=temp;
                min_index=j;
            }
        }
        insert(&Groups[min_index].second,points[i]);
    }
    //second phase
    bool changedFlag=true;
    while(changedFlag){
        rearrange(changedFlag,Groups,k);
        centroid_recalc(k,Groups);
    }

    printk(k,Groups);
    return 0; 
}