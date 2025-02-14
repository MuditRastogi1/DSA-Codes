#include<bits/stdc++.h>
using namespace std;

class FenwickTree
{
    vector<int> BIT;
    public:
    FenwickTree(int n) {
        BIT.resize(n+1);
    }

    void update(int i, int delta)
    {
        for(; i<int(BIT.size()); i += (i&-i)) {
            BIT[i] += delta;
        }
    }

    int query(int i)
    {
        int sum = 0;
        for(; i>0; i -= (i&-i)) {
            sum += BIT[i];
        }
     return sum;
    }

    vector<int> compressCordinates(vector<int>& arr) {
        int k = 1;
        map<int,int> mpp;

        for(auto it : arr) {
            mpp[it]++;
        }
        for(auto it : mpp) {
            mpp[it.first] = k++;
        }
        for(auto &it : arr) {
            it = mpp[it];
        }
     return arr;
    }
};

vector<int> solve(vector<int>& a, vector<vector<int>>& query) {
    FenwickTree ft(a.size()+2);
    vector<int> ans;
    for(int i=0; i<a.size(); i++) {
        ft.update(i+1,a[i]);
    }

    for(auto q : query) {
        if(q[0] == 1) {
            ft.update(q[1],-a[q[1]-1]+q[2]);
            a[q[1]-1] = q[2];
        }
        else {
            int l = q[1], r = q[2];
            int curr = 0;
            for(int i=l; i<=r; i++) {
                for(int j=i; j<=r; j++) {
                    curr += (ft.query(j) - ft.query(i-1));
                }
            }
            ans.push_back(curr);
        }
    }
 return ans;
}

int main()
{
    vector<vector<int>> query = {{1,2,2},{2,1,3}};
    vector<int> a = {2,1,4,3,1};
    vector<int> ans = solve(a,query);

    for(auto it : ans) cout<<it<<" ";
    // FenwickTree ft(4);
    // for(int i=0; i<4; i++) {
    //     ft.update(i+1,arr[i]);
    //     cout<<ft.query(i+1)<<" ";
    // }

    //create(arr);

    // arr = compressCordinates(arr);
    // for(auto it : arr) {
    //     cout<<it<<" ";
    // }
    
    // cout<<query(5);
    return 0;
}