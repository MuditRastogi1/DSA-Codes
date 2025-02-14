#include<bits/stdc++.h>
using namespace std;
 
class SegmentTree
{
  int len;
  vector<int> seg;

   void combine(int ind) { 
		  seg[ind] = seg[2*ind+1] + seg[2*ind+2]; 
	 }
   
    void build(int ind, int low, int high, vector<int>& arr)
    {
        if(low == high) {
            seg[ind] = arr[low];
            return;
         }
      int mid = (low + high)/2;
      build(2*ind+1,low,mid,arr);
      build(2*ind+2,mid+1,high,arr);
      combine(ind);
    }

    int query(int ind, int low, int high, int l, int r)
    {
      if(low > r || high < l)
        return 0;
                                  
      if(l <= low && high <= r)
        return seg[ind];
      
      int mid = (low + high)/2;
      int left = query(2*ind+1,low,mid,l,r);
      int right = query(2*ind+2,mid+1,high,l,r);
      return left + right;
    }

    void update(int ind, int low, int high, int index, int val)
    {
        if(low == high) {
            seg[ind] = val;
            return;
        }
        int mid = (low + high)/2;
        if(index <= mid)
          update(2*ind+1,low,mid,index,val);
        else
         update(2*ind+2,mid+1,high,index,val);
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



//////////////////////////////////////////////////////////////////////////////////////////////



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
		if(low>=l && high <= r) {
			lazy[ind] += val;
      push(ind,low,high);
			return; 
		}

		// partial overlap
		int mid = (low + high) >> 1; 
		update(2*ind+1, low, mid, l, r, val);
		update(2*ind+2, mid+1, high, l, r, val); 
		combine(ind);
	}

	void update(int ind, int low, int high, int index, int val) //point update (0,0,n-1,index,val)
    {
        push(ind,low,high);
        if(low == high)
        {
            seg[ind] = val;
            return;
        }
        int mid = (low + high)/2;
        if(index <= mid)
          update(2*ind+1,low,mid,index,val);
        else
         update(2*ind+2,mid+1,high,index,val);
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
		if(low>=l && high <= r) return seg[ind]; 
 
    //partial overlap
		int mid = (low + high) >> 1; 
		int left = query(2*ind+1, low, mid, l, r);
		int right = query(2*ind+2, mid+1, high, l, r);
		return left + right; 
	}

    public: 
    SegmentTreeLazy(int n) {
      len = n;
      seg.resize(4 * len); 
      lazy.resize(4 * len); 
    }
    void build(vector<int>& arr) {
      build(0,0,len-1,arr);
    }

    void update(int index, int val) {
      update(0,0,len-1,index,val);
    }

    void update(int l, int r, int val) {
      update(0,0,len-1,l,r,val);
    }

    int query(int l, int r) {
      return query(0,0,len-1,l,r);
    }
};

int main()
{
    int n = 5;
    vector<int> arr = {1,2,3,4,5};
    SegmentTree st(5);

    st.build(arr);
    st.update(3,100); 
    for(int i=0; i<n; i++) {
      cout<<st.query(i,i)<<" ";
    } 
    for(int i=0; i<n; i++) {
      cout<<st.query(i,i)<<" ";
    }
    cout<<"\n"<<st.query(0,4);
    return 0;
}




/////////////////////////////////////////////////////////////////////////////////


class LazySegmentTree {
    struct Node {
        int min_val;
        int count;
        int lazy;
    };

    vector<Node> tree;
    int n;

    void buildTree(int v, int tl, int tr) {
        if (tl == tr) {
            tree[v] = {0, 1, 0};
        } else {
            int tm = (tl + tr) / 2;
            buildTree(v*2, tl, tm);
            buildTree(v*2+1, tm+1, tr);
            merge(v);
        }
    }

    void apply(int v, int tl, int tr, int val) {
        tree[v].min_val += val;
        tree[v].lazy += val;
    }

    void push(int v, int tl, int tr) {
        if (tree[v].lazy != 0) {
            int tm = (tl + tr) / 2;
            apply(v*2, tl, tm, tree[v].lazy);
            apply(v*2+1, tm+1, tr, tree[v].lazy);
            tree[v].lazy = 0;
        }
    }

    void merge(int v) {
        if (tree[v*2].min_val < tree[v*2+1].min_val) {
            tree[v].min_val = tree[v*2].min_val;
            tree[v].count = tree[v*2].count;
        } else if (tree[v*2].min_val > tree[v*2+1].min_val) {
            tree[v].min_val = tree[v*2+1].min_val;
            tree[v].count = tree[v*2+1].count;
        } else {
            tree[v].min_val = tree[v*2].min_val;
            tree[v].count = tree[v*2].count + tree[v*2+1].count;
        }
    }

    void updateRange(int v, int tl, int tr, int l, int r, int addend) {
        if (l > r) return;
        if (l == tl && r == tr) {
            apply(v, tl, tr, addend);
        } else {
            push(v, tl, tr);
            int tm = (tl + tr) / 2;
            updateRange(v*2, tl, tm, l, std::min(r, tm), addend);
            updateRange(v*2+1, tm+1, tr, std::max(l, tm+1), r, addend);
            merge(v);
        }
    }

    pair<int, int> queryRange(int v, int tl, int tr, int l, int r) {
        if (l > r) return {INT_MAX, 0};
        if (l <= tl && tr <= r) {
            return {tree[v].min_val, tree[v].count};
        }
        push(v, tl, tr);
        int tm = (tl + tr) / 2;
        auto left = queryRange(v*2, tl, tm, l, std::min(r, tm));
        auto right = queryRange(v*2+1, tm+1, tr, std::max(l, tm+1), r);
        if (left.first < right.first) {
            return left;
        } else if (left.first > right.first) {
            return right;
        } else {
            return {left.first, left.second + right.second};
        }
    }

public:
    LazySegmentTree(int _n) {
    	n = _n;
        tree.resize(4*n);
        buildTree(1, 0, n-1);
    }

    void updateRange(int l, int r, int addend) {
        updateRange(1, 0, n-1, l, r, addend);
    }

    pair<int, int> queryRange(int l, int r) {
        return queryRange(1, 0, n-1, l, r);
    }
    
    int get_maintained(){
    	pair<int, int> res = queryRange(0, n-1);
    	// assert(res.first == 0);
    	return n - res.second;
    };
};



///////////////////////////////////////////////////////


class SegmentTree
{
  int len;
  vector<int> seg;

   void combine(int ind) { 
		  seg[ind] = max(seg[2*ind+1], seg[2*ind+2]); 
	 }
   
    void build(int ind, int low, int high, vector<int>& arr)
    {
        if(low == high) {
            seg[ind] = arr[low];
            return;
         }
      int mid = (low + high)/2;
      build(2*ind+1,low,mid,arr);
      build(2*ind+2,mid+1,high,arr);
      combine(ind);
    }

    int query(int ind, int low, int high, int l, int r)
    {
      if(low > r || high < l)
        return INT_MIN;
                                  
      if(l <= low && high <= r)
        return seg[ind];
      
      int mid = (low + high)/2;
      int left = query(2*ind+1,low,mid,l,r);
      int right = query(2*ind+2,mid+1,high,l,r);
      return max(left, right);
    }

    void update(int ind, int low, int high, int index, int val)
    {
        if(low == high) {
            seg[ind] = val;
            return;
        }
        int mid = (low + high)/2;
        if(index <= mid)
          update(2*ind+1,low,mid,index,val);
        else
         update(2*ind+2,mid+1,high,index,val);
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
