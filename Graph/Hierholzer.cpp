//Heirholzer algo -> eulerian path and circuit

#include<bits/stdc++.h>
using namespace std;

// for directed edges
int main()
{
  ios::sync_with_stdio(false);
  cin.tie(0);

  int n,m;
  cin>>n>>m;
  vector<vector<int>>adj(n+1);
  vector<int>indeg(n+1),outdeg(n+1);
  for(int i=0;i<m;i++)
  {
    int u,v;
    cin>>u>>v;
    adj[u].push_back(v);
    adj[v].push_back(u);
  
    indeg[v]++;
    outdeg[u]++;
  }

  if(outdeg[1]-indeg[1]!=1 || indeg[n]-outdeg[n]!=1)
  {
    cout<<"Impossible"<<endl;
    return 0;
  }

  for(int i=2;i<n;i++)
  {
    if(outdeg[i]!=indeg[i])
    {
      cout<<"Impossible"<<endl;
      return 0;
    }
  }

  vector<int>path;
  stack<int>st;
  st.push(1);
  while(!st.empty())
  {
    int v =st.top();
    if(!adj[v].empty())
    {
      int u = adj[v].back();
      adj[v].pop_back();
      st.push(u);
    }
    else{
      path.push_back(v);
      st.pop();

    }
  }

  reverse(path.begin(),path.end());
  for(auto x:path)
  {
    cout<<x<<" ";
  }
  cout<<"\n";
  return 0;


}