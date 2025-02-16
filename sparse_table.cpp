#include<bits/stdc++.h>
using namespace std;

class SparseTable {
    vector<vector<int>> sparse; // sparse[i][j] is operation among arr[i..i+2^j-1]
    vector<int> bin_log;

    public:
    SparseTable(int n) {
        sparse.resize(n, vector<int>(20));
        bin_log.resize(n + 1);
        bin_log[1] = 0; //for quickly finding log2()

        for(int i = 2; i <= n; i++) {
            bin_log[i] = bin_log[i/2]+1;
        }
    }

    int combine(int a, int b) {
        return max(a, b); //only for idempotent functions (and, or, min, max, gcd, lcm)
    }

    void build(vector<int>& arr) {
        for(int i=0; i<int(arr.size()); i++) {
            sparse[i][0] = arr[i];
        }

        for(int j=1; j<20; j++) {
            for(int i=0; i+(1<<j)-1<int(arr.size()); i++) {
                sparse[i][j] = combine(sparse[i][j-1],sparse[i+(1<<(j-1))][j-1]);
            }
        }
    }

    int query(int l, int r) {
        int len = r - l + 1;
        int k = bin_log[len]; // while((1<<(k+1)) <= len) k++;
        return combine(sparse[l][k],sparse[r-(1<<k)+1][k]);
    }
};

int main()
{
    int n,q;
    cin >> n >> q;
    vector<int> arr(n);

    for(int i=0; i<n; i++) {
        cin >> arr[i];
    }

    SparseTable st(n);
    //pre-processing
    st.build(arr);

    //answer queries in O(1)
    for(int i=0; i<q; i++) {
        int l,r;
        cin>>l>>r;
        cout<<st.query(l,r)<<endl;
    }
    return 0;
}