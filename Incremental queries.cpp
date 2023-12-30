//link -> https://www.hackerearth.com/practice/data-structures/advanced-data-structures/segment-trees/practice-problems/algorithm/incremental-queries-a7a71194/

#include<bits/stdc++.h>
using namespace std;
typedef long long int ll;
ll a[200001];
struct obj{
    ll sum,odd,even,maxm;
};
obj ans;
obj seg_tree[4*200001];
void build(int index,int l,int r){
    if(l==r){
        seg_tree[index].sum=a[l];
        seg_tree[index].odd=(a[l]%2);
        seg_tree[index].even=(a[l]%2==0?1:0);
        seg_tree[index].maxm=a[l];
        return ;
    }
    ll mid=(l+r)/2;
    build(2*index+1,l,mid);
    build(2*index+2,mid+1,r);
    seg_tree[index].sum=seg_tree[2*index+1].sum+seg_tree[2*index+2].sum;
    seg_tree[index].odd=seg_tree[2*index+1].odd+seg_tree[2*index+2].odd;
    seg_tree[index].even=seg_tree[2*index+1].even+seg_tree[2*index+2].even;
    seg_tree[index].maxm=max({seg_tree[2*index+1].maxm,seg_tree[2*index+2].maxm});
}
void update(int index,int l,int r,int node,ll val){
    if(l==r){
       seg_tree[index].sum=val;
        seg_tree[index].odd=(val%2);
        seg_tree[index].even=(val%2==0?1:0);
        seg_tree[index].maxm=val;
        a[l]=r;
       return ; 
    }
    int mid=(l+r)/2;
    if(node>=l && node<=mid) update(2*index+1,l,mid,node,val);
    else update(2*index+2,mid+1,r,node,val);
    seg_tree[index].sum=seg_tree[2*index+1].sum+seg_tree[2*index+2].sum;
    seg_tree[index].odd=seg_tree[2*index+1].odd+seg_tree[2*index+2].odd;
    seg_tree[index].even=seg_tree[2*index+1].even+seg_tree[2*index+2].even;
    seg_tree[index].maxm=max({seg_tree[2*index+1].maxm,seg_tree[2*index+2].maxm});
}
void query(int index,int low,int high,int l,int r){
    //cout<<index<<" "<<low<<" "<<high<<" "<<l<<" "<<r<<endl;
    if(low>=l && high<=r){
        ans.sum+=seg_tree[index].sum;
        ans.odd+=seg_tree[index].odd;
        ans.even+=seg_tree[index].even;
        ans.maxm=max(ans.maxm,seg_tree[index].maxm);
        return;
    }
    if(low>r || high<l){
        return;
    }
    ll mid=(low+high)/2;
    query(2*index+1,low,mid,l,r);
    query(2*index+2,mid+1,high,l,r);
}
ll solve(ll l, ll r,ll n){
    l--; r--;
    ans.sum=0; ans.odd=0; ans.even=0; ans.maxm=0;
    query(0,0,n-1,l,r);
    ll res=0,to_sum;
    to_sum=ans.maxm*(r-l+1);
    to_sum-=ans.sum;
    if(ans.maxm%2==1){
        res=(to_sum+ans.even)/2;
    }
    else{
        res=(to_sum+ans.odd)/2;
    }
    return res;
}
int main() {
    ll n,m;
    cin>>n>>m;
    for(int i=0;i<n;i++){
        cin>>a[i];
    }
    build(0,0,n-1);
    while(m--){
        ll type,l,r;
        cin>>type>>l>>r;
        if(type==1){
            l--;
            update(0,0,n-1,l,r);
        }
        else{
            cout<<solve(l,r,n)<<endl;
        }
    }
	return 0;
}
