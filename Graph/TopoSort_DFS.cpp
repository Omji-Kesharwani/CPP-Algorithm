#include<bits/stdc++.h>
using namespace std;
vector<vector<int>> adj;
vector<int>topOrder;
vector<bool>visited;

void dfs(int node)
{
  visited[node]=true;
  for(auto it: adj[node])
  {
    if(!visited[it])
    {
      dfs(it);
    }
  }
  topOrder.push_back(node);
}

int main()
{
    // Topological Sort using DFS
    // TC: O(V+E)
    // SC: O(V+E) + O(V) + O(V) = O(3V) = O(V)
    // V = no. of vertices
    // E = no. of edges
    // V+E = no. of nodes in the adjacency list

    int n, m;
    cin >> n >> m;
    adj.assign(n+1);
    visited.assign(n+1, false);
    for (int i = 0; i < m; i++)
    {
        int u, v;
        cin>>u>>v;
        adj[u].push_back(v);
    }

    for(int i=1;i<=n;i++)
    {
      if(!visited[i])
      {
        dfs(i);
      }
    }
    reverse(topOrder.begin(), topOrder.end());

    for(auto x: topOrder)
    cout<<x<<" ";

    cout<<endl;
}