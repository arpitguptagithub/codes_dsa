#include <bits/stdc++.h>
using namespace std;
#define loop(o,n) for(int i=o;i<n && i<5+o ;i++)
#define fr(o,n) for(int i=o;i<n ;i++)

vector<pair<int,double>> v1;
vector<int> d;
int median(vector<int> a,int k){
  //  return 2;
    vector<int> s;
    loop(k,a.size()){
        s.push_back(v1[a[i]].first);
    }
   // cout<< k;
    int m=s.size()/2;
    sort(s.begin(),s.end());
     m=s[m];
     s.clear();
     int r=m;
    loop(k,a.size()){
        if(v1[a[i]].first==m){
       // cout<<i;
          return a[i];
          break;}
    }
    return 0;
}

int weighted(vector<int> a,int l,int h){
      vector<int> na; 
      fr(l,h){
        na.push_back(median(a,i));
        i=i+4;
      }
      if(na.size()==1)
        return na[0];
     else return weighted(na,0,na.size());

}
//median of median code is correct

/*int right(int p,int l,int h){
    if(l==h)
        return p;
    while(v1[p]<v1[h] && h>l){
        if(p=h)
           return left(p,l,p);
          h--;}
    swap(v1[p],v1[h]);
    return left(h,p,h);
}
int left(int p,int l,int h){
    if(l==h) 
      return p;
    while(v1[p]>v1[l] && l<h) l++;
    swap(v1[p],v1[l]);
    return right(l,l,p);
}*/
int partition(int p,int l,int h){
    int k;
    if(l==h) return l;

    if(p==h){
         while(v1[p].first>=v1[l].first ){
            if(p==l) return l;
            l++;}
        swap(v1[p],v1[l]);
         return partition(l,l,p-1);
    }
    else{
         while(v1[p].first<=v1[h].first ){
          // if(l==h) return h; 
        if(p==h)
           return partition(p,l,p);
          h--;
           if(l==h) return h; }
      swap(v1[p],v1[h]);
        return partition(h,p+1,h);
    }
}

//fr comparing double
int comp(double a,double b){
   
    a=a*100;
    b=b*100;
    int k=int(a-b);
    if(k==0) return 1;
    else return 0;

}
int greatest(int k){
  int d=v1[0].first;
    fr(1,k){
      if(v1[i].first>d)
         d=v1[i].first;
    }
    return d;
}
int select(double q,int l,int h){
         int k= weighted(d,l,h);
         if(h<4)
           k=h-1;
         k=partition(k,l,h-1);
         cout<<k<<endl; 
         fr(0,k+1)cout<<v1[i].first; cout<<endl;
         double m=0.0;
         fr(0,k+1){
            m+=v1[i].second;
         }
         cout<<m<<endl;
        if(comp(m,q)) return v1[k].first;
        else if(m>q){
             if(comp(m-v1[k].second,q) || m-v1[k].second<q) return greatest(k);
            
            else return select(q,l,k);  
        }
        else{
            return select(q,k+1,h);
        }
         
}


int main(){
    int b[8]={1,2,3,4,5,6,7,8};
    double c[8]={0.1,0.2,0.05,0.05,0.2,0.1,0.05,0.25};

    fr(0,8){
        v1.push_back(make_pair(b[i],c[i]));
        d.push_back(i);
    }
   /*// swap(v1[0],v1[0]);
    //fr(0,8){ cout<<v1[i].first<<endl;}
   int k= weighted(d,0,8);
   //cout<<k;
   k=partition(k,0,7);
   cout<<k;
   fr(0,8){ cout<<v1[i].first<<endl;}*/
  cout<<select(0.76,0,8);

  
   
}

