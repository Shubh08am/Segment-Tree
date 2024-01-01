class SegTree{
public:
SegTree(int n){
    this->n=n;
    tree.resize(4*n);
}
void update(int ind,int val){
    update(ind,val,0,n-1,0);
}
int query(int x,int y){
    return query(x,y,0,n-1,0);
}
private:
int n;
vector<int>tree;
void update(int ind,int val,int l,int r,int i){
    if(l==r){
        tree[i]=val;
        return;
    }
    int m=l+(r-l)/2;
    if(m>=ind) update(ind,val,l,m,i*2+1);
    else update(ind,val,m+1,r,i*2+2);
    tree[i]=max(tree[i*2+1],tree[i*2+2]);
}
int query(int x,int y,int l,int r,int i){
    if(l>y || r<x) return 0;
    if(x<=l && r<=y){
        return tree[i];
    }
    int m=l+(r-l)/2;
    return max(query(x,y,l,m,i*2+1),query(x,y,m+1,r,i*2+2));
}
};

class Solution {
public:
    int lengthOfLIS(vector<int>& nums) {
        vector<pair<int,int>>val_and_ind; 
        int n=nums.size();
        for(int i=0;i<n;i++) val_and_ind.push_back({nums[i],i});
        sort(val_and_ind.begin(),val_and_ind.end());
        //In sorted order which index of old array -> appears where (index) in new array
        map<int,int>position; 
        for(int i=0;i<n;i++){
            position[val_and_ind[i].second]=i;
        }
        SegTree seg(n);
        for(int i=0;i<n;i++){
            int sorted_ind=position[i];
            int lb = lower_bound(val_and_ind.begin(),val_and_ind.end(),make_pair(nums[i],-1))-val_and_ind.begin();
            //if lb>0 than only benefit of doing query before that position
            int val=1+(lb>0?seg.query(0,lb-1):0);
            seg.update(position[i],val);
        }
    return seg.query(0,n-1);//at last in tree find max value by query 
    }
};
