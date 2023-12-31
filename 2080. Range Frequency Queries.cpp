//Merge sort Tree -> https://leetcode.com/problems/range-frequency-queries/solutions/1589039/merge-sort-tree-segment-tree/ 
class SegTree{
public:
SegTree(int n,vector<int>&arr){
    this->n=n; 
    tree.resize(4*n);
    build(0,n-1,0,arr);
}
int query(int x,int y,int val){
    return query(x,y,val,0,n-1,0);
}
private:
int n;
vector<unordered_map<int,int>>tree;
void build(int l,int r,int i,vector<int>&arr){
    if(l==r){
        tree[i][arr[l]]++;
        return;
    }
    int m=l+(r-l)/2;
    build(l,m,i*2+1,arr);
    build(m+1,r,i*2+2,arr);
    for(auto & [key,val] : tree[i*2+1]) tree[i][key]+=val ;
    for(auto & [key,val] : tree[i*2+2]) tree[i][key]+=val ;
}
int query(int x,int y,int val,int l,int r,int i){
    // y x l r -> no overlap [l,r]
    if(l>y || r<x) return 0;
    // x l r y -> overlap [l,r]
     if(l>=x && r<=y){
        return tree[i][val];
    }
    int m=l+(r-l)/2;
    return query(x,y,val,l,m,i*2+1) + query(x,y,val,m+1,r,i*2+2); 
}
};
class RangeFreqQuery {
public:
    SegTree * seg ; 
    RangeFreqQuery(vector<int>& arr) {
        int n=arr.size();
        seg=new SegTree(n,arr) ;
    }
    
    int query(int left, int right, int value) {
        return seg->query(left,right,value);
    }
};

/**
 * Your RangeFreqQuery object will be instantiated and called as such:
 * RangeFreqQuery* obj = new RangeFreqQuery(arr);
 * int param_1 = obj->query(left,right,value);
 */
