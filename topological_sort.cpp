#include<bits/stdc++.h>
using namespace std;
 
vector<int> topoSort(int n, vector<vector<int>>& edges) {
    vector<int> topo;
    vector<int> adj[n];
    vector<int> indegree(n,0);

    for(auto e : edges) { // edges format :  u -> v 
        adj[e[0]].push_back(e[1]);
        indegree[e[1]]++;
    }

  for(int i=0; i<n; i++) {
      if(indegree[i] == 0)
        topo.push_back(i);
  }

    for(int i=0; i<topo.size(); i++) {
      for(auto child : adj[topo[i]]) {
            indegree[child]--;
            if(indegree[child] == 0)
              topo.push_back(child);
        }
    }
  return topo;
}

int main()
{
    return 0;
}