#include "avl.h"
using namespace std;


int main(){
    AVL avl;
    priority_queue<pos, vector<pos>, CompareX> pq;
    
    cout<<pq.size()<<endl;
    vector <pair<int,int>> ans;
    while(pq.top().hv)  pq.pop();
    Node* root = new Node(pq.top().a, pq.top().b);
    pq.pop();
    while(pq.size()>0){
        if(pq.top().hv==0){
            if(!pq.top().se){
                avl.insert(&root, pq.top().a, pq.top().b);
            }
            else{
                avl.remove(&root, pq.top().a, pq.top().b);
            }
            pq.pop();
        }
        else{
            pos a = pq.top();
            if(pq.size()>2)
                pq.pop();
            pos b = pq.top();
            if(pq.size()>1)
                pq.pop();
            if(a.b>b.b){
                avl.intersect(ans, root, b,a);
            }
            else {
                avl.intersect(ans, root, a,b);
            }
        }        
    }
    cout<<"\nIntersections:\n";
    if(ans.size()==0)
        cout<<"No intersections";
    else{
        for(auto i: ans)
            cout<<"("<<i.first<<","<<i.second<<")"<<endl;
    }
    return 0;
}