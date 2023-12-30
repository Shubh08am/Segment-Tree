// link -> https://www.hackerearth.com/practice/data-structures/advanced-data-structures/segment-trees/practice-problems/algorithm/range-minimum-query/

#include<bits/stdc++.h>
using namespace std; 
#define ll long long 

class SegTree{
public:
SegTree(int _n,vector<int>arr){
    n=_n;
    tree.resize(4*n,0);
    build(0,n-1,0,arr);
}
int query(int x,int y){
return query(x,y,0,n-1,0);
}
void update(int ind,int val){
update(ind,val,0,n-1,0);
}
private:
vector<ll>tree; 
int n;
void build(int l,int r,int i,vector<int>&arr){
    if(l==r){
        tree[i]=arr[l];
        return;
    }
    int m= l+(r-l)/2;
    build(l,m,i*2+1,arr);
    build(m+1,r,i*2+2,arr);
    tree[i]=min(tree[i*2+1],tree[i*2+2]) ; 
}
ll query(int x,int y,int l,int r,int i){
    //no overlap
    if(r<x || l>y) return 1e18; 
    //complete overlap 
    if(l>=x && r<=y) return tree[i]; 
    //partial overlap 
    int m=l+(r-l)/2; 
    return min(query(x,y,l,m,i*2+1),query(x,y,m+1,r,i*2+2)) ; 
}
void update(int ind,int val,int l,int r,int i){
    if(l==r){
        tree[i]=val;
        return;
    }
    int m= l+(r-l)/2;
    if(m>=ind) update(ind,val,l,m,i*2+1) ; 
    else update(ind,val,m+1,r,i*2+2);
    tree[i]=min(tree[i*2+1],tree[i*2+2]) ;
}
};

int main(){
    int n,q;
    cin>>n>>q; 
    vector<int>arr(n);
    for(int i=0;i<n;i++) cin>>arr[i] ; 
    SegTree tree(n,arr) ;
    while(q--){
        string op;
        cin>>op;
        if(op=="q"){
            int l,r;
            cin>>l>>r; 
            cout << tree.query(l-1,r-1) << "\n";
        }
        else{
            int ind,val;
            cin>>ind>>val;
            tree.update(ind-1,val);
        }
    }
return 0;
}
