#include<bits/stdc++.h>
using namespace std;

struct Edge{
  int to ; // target vertex 
  long long cap ; // remaining capacity (residual capacity)
  int rev ; // capacity of the reverse edge in graph[to]
  Edge(int _to,long long _cap,int _rev){
    to = _to;
    cap = _cap;
    rev = _rev;
  }

};

struct Dinic{
  int n;
  vector<vector<Edge>> graph;
  vector<int>level; // distance from source in level graph
  vector<int>it ; //current edge iterator for each node 
  
  Dinic(int n):n(n),graph(n),level(n),it(n){}

  // Add directed edge u-> v with capacity cap
  void add_edge(int u,int v,long long cap){
    graph[u].emplace_back(v,cap,(int)graph[v].size());
  // reverse edge v->u with 0 capacity initially
    graph[v].emplace_back(u,0,(int)graph[u].size()-1);
}

// Build level graph using BFS.Return s true if sink t is reachable.

bool bfs(int s,int t)
{
  fill(level.begin(),level.end(),-1);

  queue<int>q;
  level[s]=0;
  q.push(s);

  while(!q.empty()){
    int u=q.front();
    q.pop();

   for(const Edge &e : g[u])
   {
    if(e.cap>0 && level[e.to]<0){
      level[e.to]=level[u]+1;
      q.push(e.to);
    }
   }
  }
  return level[t]!=-1;
}

//DFS send flow in level graph.Return amount pushed.
long long dfs(int u,int t,long long f)
{
  if(u==t) return f;

  for(int &i = it[u] ; i<graph[u].size();++i)
  {
    Edge &e = graph[u][i];
    if(e.cap <= 0) continue; // no residual capacity

    if(level[e.to]!=level[u]+1) continue;// must go to next level
    long long pushed = dfs(e.to,t,min(f,e.cap));

    if(pushed > 0)
    {
      e.cap -= pushed; // decrease the residual forward
      g[e.to][e.rev].cap += pushed; // increase the  residual backward
      return pushed;
    }
  }

  return 0 ; // no flow could could be pushed from u 

}

long long max_flow(int s,int t)
{
  long long flow = 0 ;
  const long long INF = (long long)4e18;
  while(bfs(s,t))
  {
    fill(it.begin(),it.end(),0);
    while(true)
    {
      long long pushed = dfs(s,t,INF);
      if(pushed == 0) break;
      flow += pushed;
    }
  } 
  return flow ;
}
};

int main()
{
  ios::sync_with_stdio(false);
  cin.tie(0);

  int n,m;
  cin>>n>>m;
  Dinic dinic(n);
  for(int i=0;i<m;i++)
  {
    int a,b;
    
    long long c;
    cin>>a>>b>>c;
    a--; b--;
    dinic.add_edge(a,b,c);
  }

  long long maxFlow = dinic.max_flow(0,n-1);

  cout<<maxFlow<<endl;
  return 0;
}