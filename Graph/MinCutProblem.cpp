#include<bits/stdc++.h>
using namespace std;

struct Edge{
  int to , rev ;
  long long cap;
};

struct Dinic{
  int n;
  vector<vector<Edge>> g;
  vector<int>level ,it;

  Dinic(int n){
    this->n = n;
    g.resize(n);
    level.resize(n);
    it.resize(n);
  }

  void addEdge(int u,int v,long long cap){
    g[u].push_back({v,(int)g[v].size(),cap});
    g[v].push_back({u,(int)g[u].size()-1,0});//reverse edge with capacity 0
  
  }
  bool bfs(int s,int t)
  {
    fill(level.begin(),level.end(),-1);
    queue<int>q;
    q.push(s);
    level[s] = 0;
    while(!q.empty())
    {
      int u = q.front();
      q.pop();
      for(auto &e:g[u])
      {
        if(level[e.to]==-1 && e.cap>0)
        {
          level[e.to] = level[u]+1;
          q.push(e.to);
        }
      }
    }

    return level[t]!=-1;
  }

  long long dfs(int u,int t,long long f)
  {
    if(u==t) return f;
    for(int &i=it[u];i<(int)g[u].size();i++)
    {
      Edge &e = g[u][i];
      if(level[e.to]==level[u]+1 && e.cap>0)
      {
        long long pushed  = dfs(e.to,t,min(f,e.cap));
        if(d>0)
        {
          e.cap -= pushed;
          g[e.to][e.rev].cap += pushed;
          return pushed;
        }
}
    }

    return 0;
}

long long max_flow(int s,int t)
{
  long long flow = 0;
  while(bfs(s,t))
  {
    fill(it.begin(),it.end(),0);
    while(long long pushed = dfs(s,t,LLONG_MAX))
    {
      flow += pushed;
    }
  }
  return flow;
}

// After max flow , find the nodes reachable from s in residual graph
vector<bool> reachable_from_source(int s)
{
  vector<bool>visited(n,false);
  queue<int>q;

  q.push(s);
  visited[s] = true;

  while (!q.empty())
  {
    int u =q.front();
    q.pop();
    for(auto &e: g[u])
    {
      if(!visited[e.to] && e.cap>0)
      {
        visited[e.to] = true;
        q.push(e.to);
      }
    }
  }
  return visited ;
}
};

int main()
{
  ios::sync_with_stdio(false);
  cin.tie(0);
  int n,m;
  cin>>n>>m;
  Dinic dinic(n);
  vector<pair<int,int>> edges ;
  for(int i=0;i<m;i++)
  {
    int a,b;
    cin>>a>>b;
    --a;
    --b;
    dinic.addEdge(a,b,1);
    dinic.addEdge(b,a,1);
    edges.push_back({a,b});
  }
  long long flow = dinic.max_flow(0,n-1);

  vector<bool>reachable = dinic.reachable_from_source(0);

  vector<pair<int,int>>cut;
  for(auto [a,b]:edges)
  {
    if(reachable[a] && !reachable[b])
    {
      cut.push_back({a,b});
    }
    else if(reachable[b] && !reachable[a])
    {
      cut.push_back({b,a});
    }
  }

  cout<<cut.size()<<endl;
  for(auto [a,b]:cut)
  {
    cout<<a+1<<" "<<b+1<<endl;
  }
  
  return 0;


}

