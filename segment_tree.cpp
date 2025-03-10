#include<bits/stdc++.h>
using namespace std;
 
class SegmentTree {
  int len;
  vector<int> seg;

   void combine(int ind) { 
	   seg[ind] = seg[2*ind+1] + seg[2*ind+2]; 
   }
   
    void build(int ind, int low, int high, vector<int>& arr) {
        if(low == high) {
            seg[ind] = arr[low];
            return;
         }
      int mid = (low + high)/2;
      build(2*ind+1,low,mid,arr);
      build(2*ind+2,mid+1,high,arr);
      combine(ind);
    }

    int query(int ind, int low, int high, int l, int r) {
      if(low > r || high < l)
        return 0;
                                  
      if(l <= low && high <= r)
        return seg[ind];
      
      int mid = (low + high)/2;
      int left = query(2*ind+1,low,mid,l,r);
      int right = query(2*ind+2,mid+1,high,l,r);
      return left + right;
    }

    void update(int ind, int low, int high, int index, int val) {
        if(low == high) {
            seg[ind] = val;
            return;
        }
        int mid = (low + high)/2;
        if(index <= mid) {
          update(2*ind+1,low,mid,index,val);
	}
        else {
         update(2*ind+2,mid+1,high,index,val);
	}
        combine(ind);
    }

    public:
    SegmentTree(int n) {
      len = n;
      seg.resize(4*len+1);
    }

    void build(vector<int>& arr) {
      build(0,0,len-1,arr);
    }

    void update(int index, int val) {
      update(0,0,len-1,index,val);
    }

    int query(int l, int r) {
      return query(0,0,len-1,l,r);
    }
};
