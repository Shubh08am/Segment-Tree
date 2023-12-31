//Merge sort Tree -> https://leetcode.com/problems/range-frequency-queries/solutions/1589039/merge-sort-tree-segment-tree/
//problem -> 2080. Range Frequency Queries [leetcode]

class MergeSortTree{
public:
MergeSortTree(int n,vector<int>&arr){
    this->n=n; 
    tree.resize(4*n);
    build(0,n-1,0,arr);
}
int query(int x,int y,int val){
    return query(x,y,val,0,n-1,0);
}
private:
int n;
vector<vector<int>>tree;
    vector<int> merge(vector<int>&nums1 ,vector<int>&nums2){
      int len1=nums1.size() ,  len2= nums2.size() ;
       int ind1 = 0 , ind2=0 , p = 0 ; 
       vector<int>ans;
        while(ind1<len1&&ind2<len2){
            if(nums1[ind1] < nums2[ind2]){
                    ans.push_back(nums1[ind1]); 
                    ind1++;
            }
            else {
                    ans.push_back(nums2[ind2]); 
                    ind2++;
                }
        }
        while(ind1<len1){
                    ans.push_back(nums1[ind1]); 
                    ind1++;
        }
        while(ind2<len2){
                    ans.push_back(nums2[ind2]);         
                    ind2++;
        }  
    return ans;
    }
void build(int l,int r,int i,vector<int>&arr){
    if(l==r){
        tree[i]={arr[l]};
        return;
    }
    int m=l+(r-l)/2;
    build(l,m,i*2+1,arr);
    build(m+1,r,i*2+2,arr);
    tree[i]=merge(tree[i*2+1],tree[i*2+2]);
}
int query(int x,int y,int val,int l,int r,int i){
    // y x l r -> no overlap [l,r]
    if(l>y || r<x) return 0;
    // x l r y -> overlap [l,r]
     if(l>=x && r<=y){
         //upper bound - lower bound 
        int left = lower_bound(tree[i].begin(),tree[i].end(),val)-tree[i].begin();
        int right = upper_bound(tree[i].begin(),tree[i].end(),val)-tree[i].begin(); 
        return right-left;
    }
    int m=l+(r-l)/2;
    return query(x,y,val,l,m,i*2+1) + query(x,y,val,m+1,r,i*2+2); 
}
};
class RangeFreqQuery {
public:
    MergeSortTree * seg ; 
    RangeFreqQuery(vector<int>& arr) {
        int n=arr.size();
        seg=new MergeSortTree(n,arr) ;
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
