class SegmentTreeLazy {
    int len;
      vector<int> seg, lazy; 
  
    void combine(int ind) { 
          seg[ind] = seg[2*ind+1] + seg[2*ind+2]; 
      }
  
      void push(int ind, int low, int high) {
          if(lazy[ind] != 0) {
              seg[ind] += (high - low + 1) * lazy[ind]; 
              // propogate the lazy update downwards
              // for the remaining nodes to get updated 
              if(low != high) {
                  lazy[2*ind+1] += lazy[ind]; 
                  lazy[2*ind+2] += lazy[ind]; 
              }
              lazy[ind] = 0; 
          }
      }
  
      void build(int ind, int low, int high, vector<int>& arr) {
          if(low == high) {
              seg[ind] = arr[low];
              return; 
          }
      
          int mid = (low + high) >> 1; 
          build(2*ind+1, low, mid, arr); 
          build(2*ind+2, mid+1, high, arr); 
          combine(ind);
      }
  
      void update(int ind, int low, int high, int l, int r, int val) { //range update (0,0,n-1,left,right,val)
          // update the previous remaining updates 
          // and propogate downwards 
          push(ind,low,high);
   
          // no overlap 
          if(high < l or r < low) {
              return; 
          }
   
          // complete overlap 
          if(low >= l && high <= r) {
              lazy[ind] += val;
              push(ind, low, high);
              return; 
          }
  
          // partial overlap
          int mid = (low + high) >> 1; 
          update(2*ind + 1, low, mid, l, r, val);
          update(2*ind + 2, mid+1, high, l, r, val); 
          combine(ind);
      }
  
      void update(int ind, int low, int high, int index, int val) { //point update (0,0,n-1,index,val) 
          push(ind, low, high);
          if(low == high) {
              seg[ind] = val;
              return;
          }
  
          int mid = (low + high)/2;
          if(index <= mid) {
              update(2*ind + 1, low, mid, index, val);
          }
          else {
              update(2*ind + 2, mid + 1, high, index, val);
          }
          combine(ind);
      }
  
      int query(int ind, int low, int high, int l, int r) {
          // update if any updates are remaining 
          push(ind,low,high);
   
          // no overlap return 0; 
          if(high < l or r < low) {
              return 0; 
          }
  
          // complete overlap 
          if(low >= l && high <= r) {
              return seg[ind]; 
          }
   
      //partial overlap
          int mid = (low + high) >> 1; 
          auto left = query(2*ind + 1, low, mid, l, r);
          auto right = query(2*ind + 2, mid + 1, high, l, r);
          return (left + right); 
      }
  
      public: 
      SegmentTreeLazy(int n) {
        len = n;
        seg.resize(4 * len); 
        lazy.resize(4 * len); 
      }
      void build(vector<int>& arr) {
        build(0, 0, len - 1, arr);
      }
  
      void update(int index, int val) {
        update(0, 0, len - 1, index, val);
      }
  
      void update(int l, int r, int val) {
        update(0, 0, len - 1, l, r, val);
      }
  
      int query(int l, int r) {
        return query(0, 0, len - 1, l, r);
      }
  };
