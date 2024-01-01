//link -> https://www.spoj.com/problems/KQUERY/

#include<bits/stdc++.h>
using namespace std;

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
  
  vector<int> Merge(vector<int>&nums1 ,vector<int>&nums2){
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
      tree[i]=Merge(tree[i*2+1],tree[i*2+2]);
  }
  int query(int x,int y,int val,int l,int r,int i){
      if(l>y || r<x) return 0;
      if(l>=x&&r<=y){
          int ind=upper_bound(tree[i].begin(),tree[i].end(),val)-tree[i].begin();
          return tree[i].size()-ind;
      }
      int m=l+(r-l)/2;
      return query(x,y,val,l,m,i*2+1)+query(x,y,val,m+1,r,i*2+2);
  }
};
int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
    int n;cin>>n;
    vector<int>arr(n);
    for(int i=0;i<n;i++) cin>>arr[i]; 
    MergeSortTree *seg = new MergeSortTree(n,arr);
    int q;cin>>q;
    while(q--){
        int i,j,k;
        cin>>i>>j>>k;
        cout<< seg->query(i-1,j-1,k) << "\n";
    }
	return 0;
}
