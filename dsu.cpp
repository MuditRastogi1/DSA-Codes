#include<bits/stdc++.h>
using namespace std;

class DSU {
    vector<int> parent;
    vector<int> size;
    
    public:
    DSU(int n) {
        parent.resize(n + 1);
        size.resize(n + 1);
        for(int i=0; i<n; i++) {
          make_set(i);
        }
    }

    void make_set(int v) {
        parent[v] = v;
        size[v] = 1;
    }

    int find_parent(int v) {
        if(v == parent[v]) return v;
        return parent[v] = find_parent(parent[v]);
    }

    void Union(int a, int b) {
        a = find_parent(a);
        b = find_parent(b);
    
        if(a != b) {
            if(size[a] < size[b]) {
                swap(a,b);
            }
         parent[b] = a;
         size[a] += size[b];
        }
    }
};

int main()
{
    DSU dsu(100000);
    dsu.find_parent(0);
    dsu.Union(0,1);
    return 0;
}
