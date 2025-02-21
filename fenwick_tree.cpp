#include<bits/stdc++.h>
using namespace std;

class FenwickTree {
    vector<int> BIT;
    public:
    FenwickTree(int n) {
        BIT.resize(n+1);
    }

    void update(int i, int delta) {
        for(; i<int(BIT.size()); i += (i&-i)) {
            BIT[i] += delta;
        }
    }

    int query(int i) {
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

int main() {
    vector<vector<int>> query = {{1,2,2},{2,1,3}};
    vector<int> a = {2,1,4,3,1};

    FenwickTree ft(a.size());
    for(int i=0; i<4; i++) {
        ft.update(i+1, arr[i]);
        cout << ft.query(i+1) << " ";
    }
 return 0;
}
