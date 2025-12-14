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

  int addEdge(int u,int v,long long cap){
    int idx_u = (int)g[u].size();
    int idx_v  = (int)g[v].size();
    g[u].push_back({v,cap,idx_v});
    g[v].push_back({u,0,idx_u});

    return idx_u;
  
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
};

int main()
{
  ios::sync_with_stdio(false);
  cin.tie(0);

  int n,m,k;
  cin>>n>>m>>k;
  int S = 0 ;
  int offsetB=1;
  int offsetG = 1+n;
  int T = 1+n+m;
  int N = T+1;
  
  Dinic dinic(N);

  // edgesTocheck will store (boyNode,edgeIndexInG[boy]) for each boy -> girl added 
  // so we can test later if that forward edge was used .

  vector<tuple<int,int,int>> edge_list; // store (boyNode,girlNode,edgeIndex)

  // connect source -> boys 
  for(int b =0;b<n;b++)
  {
    dinic.addEdge(S,offsetB+b,1);
  }

  // read possible pairs and add boy -> girl edges(cap 1)

  for(int i=0;i<k;i++)
  {
    int b,g;
    cin>>b>>g;
    b--;
    g--;
   int idx = dinic.addEdge(offsetB+b,offsetG+g,1);
 edge_list.emplace_back(b,idx,g);
  }

  for(int g=0;g<m;g++)
  {
    dinic.addEdge(offsetG+g,T,1);
  }

  long long flow = dinic.max_flow(S,T);
  //extract matching by checking for each recorded forward edge whether its cap is 0 . the forward edge is g[boyNode][idx].

  vector<pair<int,int>> matching ;
  for(auto &tup : edge_list)
  {
    int boyNode,idx,girlNode;
    tie(boyNode,idx,girlNode) = tup;

    Edge &e = dinic.g[boyNode][idx];
    if(e.cap==0)
    {
      int boyId = boyNode - offsetB+1;
      int girlId = girlNode - offsetG+1;
      matching.emplace_back(boyId,girlId);
    }
  }

  cout<<matching.size()<<endl;
  for(auto &p:matching)
  {
    cout<<p.first<<" "<<p.second<<endl;
  }
  return 0;
}