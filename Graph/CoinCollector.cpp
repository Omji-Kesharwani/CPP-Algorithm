
#include<bits/stdc++.h>
using namespace std;


vector<int>value , component ,topOrder ;// value ->coins at each node , component[i] -> stores the compId of each node , topOrder -> stores the topological order of the  condensed graph nodes
vector<vector<int>>graph,graphRev,sccGraph; // graph -> stores the graph , graphRev -> stores the reverse graph , sccGraph -> stores the condensed graph
vector<long long > sccValue ; // stores the value of each strongly connected component
vector<bool>visited;// boolean array to store which node is visited or not
stack<int>finishStack ;// stores the toposort of the given graph

void dfsForward(int node) // to perform the topological sort of the original graph
{
  if(visited[node]) return ;

  visited[node]=true;

  for(auto ngb : graph[node])
  {
    if(!visited[ngb])
    dfsForward(ngb) ;
  }

  finishStack.push(node) ;
}

void dfsReverse(int node ,int compId,long long &sum ) // reverse the graph , assign the component id and store the sum of each ssc 
{
  component[node] =compId ;
  sum += value[node] ;

  for(int ngb : graphRev[node])
  {
    if(component[ngb]==-1)
    {
      dfsReverse(ngb,compId,sum) ;
    }
  }
}

void buildCondensedGraph(int n,int numComponents)// build the condensed graph
{
  sccGraph.assign(numComponents,vector<int>());

  for(int u=1;u<=n;u++)
  {
    for(int v:graph[u])
    {
        if(component[u]!=component[v])
        {
          sccGraph[component[u]].push_back(componet[v]);
        }
    }
  }
}

void computeTopologicalSort(int numComponents) //using kanhs algo to compute the topological sort of the condensed graph
{
  vector<int>indegree(numComponents,0);

  for(int u=0;u<numComponents;u++)
  {
    for(int v : sccGraph[u])
    {
      indegree[v]++;
    }
  }

  queue<int>q;
  for(int u=0;u<numComponents;u++)
  {
    if(indegree[u]==0)
    q.push(u) ;
  }

  while(!q.empty())
  {
    int u = q.front();
    q.pop();
    topOrder.push_back(u);

    for(int v:sccGraph[u])
    {
      indegree[v]--;
      if(indegree[v]==0)
      {
        q.push(v);
      }
    }
  }
}
int main()
{
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  int n,m; // n->number of nodes , m->number of edges
  cin>>n>>m;
  
  value.resize(n+1); // value[i]-> coins at node i
  for(int i=1;i<=n;i++)
  cin>>value[i] ;

  graph.assign(n+1,vector<int>()); // build the graph
  graphRev.assign(n+1,vector<int>());// build the reverse graph

  for(int i=0;i<m;i++) // taking the input
  {
    int u,v;
    cin>>u>>v;
    graph[u].push_back(v);
    graphRev[v].push_back(u);
  }

  visited.assign(n+1,false);// to check if the node is visited or not

  // To perform the topological sort 
  // Also to check the disconnected components  
  for(int i=1;i<=n;i++)
  {
    if(!visited[i])
    dfsForward(i) ;
  }

  component.assign(n+1,-1); // assign the component id to each node of a particular component
  int numComponents = 0 ;// no of total components

  sscValue.clear();// store the total-value of each strongly connected component

  while(!finishStack.empty())  // performing the kosaraju algo from the topo sort 
  {
    int node = finishStack.top();
    finishStack.pop();
    if(component[node]==-1)          // calculate the total value of each component
    {
      long long sum = 0 ;                        
      dfsReverse(node,numComponents++,sum) ;
      sccValue.push_back(sum) ;
    }
  }

  buildCondensedGraph(n,numComponents); // building the condensed graph
  computeTopologicalSort(numComponents); // compute toposort of the condensed graph

  vector<long long >dp(numComponents,0); // dp[i] -> maximum coins that can be collected from component i

  for(int u:topOrder)  // storing the maximum coins that can be collected from each component
  {
    dp[u]+=sccValue[u];

    for(int v:sccGraph[u])
    {
      dp[v] = max(dp[v],dp[u]);
    }
  }

  cout<< *max_element(dp.begin(),dp.end()) <<endl; // returning the max coins that can be collected

  return 0;


}