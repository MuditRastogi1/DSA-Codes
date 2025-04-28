    int timer;
    vector<int> size, pathSum, myParent, node2index, currValue;

    int dfs(int node, int parent, int edgeWeight, int currPathSum, vector<vector<vector<int>>>& adj) {
        int index = timer++, currSubtreeSize = 1;
        pathSum[index] = currPathSum;
        currValue[index] = edgeWeight;
        node2index[node] = index;

        for(auto it : adj[node]) {
            int child = it[0], weight = it[1];
            if(child != parent) {
                myParent[child] = node;
                currSubtreeSize += dfs(child, node, weight, currPathSum + weight, adj);
            }
        }

        size[index] = currSubtreeSize;
        return currSubtreeSize;
    }
public:
    void preprocess(int n) {
        timer = 0;
        size.resize(n);
        pathSum.resize(n);
        myParent.resize(n);
        node2index.resize(n);
        currValue.resize(n);
    }
    vector<int> pathQueries(int n, vector<vector<vector<int>>>& adj, vector<vector<int>>& queries) {
        preprocess(n);
        vector<int> ans;
        
        dfs(0, -1, 0, 0, adj);

        SegmentTreeLazy st(n);
        st.build(pathSum);

        for(auto q : queries) {
            int type = q[0];
            if(type == 1) { //update edge value (u -> v)
                int u = q[1] - 1, v = q[2] - 1, w = q[3];
                if(myParent[u] == v) {
                    swap(u, v); //ensuring u is parent of v
                }
                int index = node2index[v], diff = w - currValue[index];
                st.update(index, index + size[index] - 1, diff);
                currValue[index] = w;
            }
            else { //query for a path ending at node x
                int x = q[1] - 1;
                ans.push_back(st.query(node2index[x]));
            }
        }
     return ans;
    }
