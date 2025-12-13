 //Prims Algorithm
 #include<bits/stdc++.h>
using namespace std;

int main()
{
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  int n,m;
  cin>>n>>m;
  vector<vector<pair<int,int>>> adj(n+1);
  vector<int>visited(n+1,false);
  for(int i=0;i<m;i++)
  {
    int u,v,w;
    cin>>u>>v>>w;
    adj[u].push_back({v,w});
    adj[v].push_back({u,w});
  }

  priority_queue<pair<int,int>,vector<pair<int,int>>,greater<>> pq;
  long long res =0;
  pq.push({0,1});

  while(!pq.empty())
  {
    auto [d,u]=pq.top();
    pq.pop();
    if(visited[u])continue;
    visited[u]=true;

    res += d;
    
    for(auto [v,w]:adj[u])
    {
      if(!visited[v])
      {
        pq.push({w,v});
      }
    }
  }

  for(int i=0;i<n;i++)
  {
    if(!visited[i])
    {
      cout<<"-1\n";
      return 0;
    }
  }

  cout<<res<<'\n';

  return 0;
}