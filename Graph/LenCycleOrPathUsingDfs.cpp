#include<bits/stdc++.h>
using namespace std;

vector<int>arr; // arr[u] = the planet teleportation target from planet u
vector<int>dp // dp[u]= cycle length if u is in the cycle or distance to cycle +cycle length
vector<int>visited;
vector<int>dist;
int cycle_start=-1;
int cycle_len=0;

void dfs(int u,int current_dist)
{
  if(visited[u]) return;
  dist[u]=current_dist;
  visited[u]=true;

  int v = arr[u];
  if(!visited[v])
  {
    dfs(v,current_dist+1);
  }
  else{
    if(dp[v]==0)
    {
      cycle_len = dist[u]-dist[v]+1;
      cycle_start = v;
    }
    else{
      cycle_len = dp[v];
    }
  }

  if(cycle_start!=-1)
  {
    dp[u]=cycle_len;
    if(u==cycle_start)
    cycle_start=-1;
  }
  else{
    dp[u]=dp[v]+1;
  }

}
int main()
{
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  int n;
  cin>>n;
  arr.resize(n+1);
  dp.resize(n+1,0);
  visited.resize(n+1,false);
  dist.resize(n+1,0);

  for(int i=1;i<=n;i++) cin>>arr[i];

  for(int i=1;i<=n;i++)
  {
    if(!visited[i])
    {
      cycle_start=-1;
      cycle_len=0;
      dfs(i,1);
    }
  }

  for(int i=1;i<=n;i++)
  {
    cout<<dp[i]<<' ';
  }


  return 0;
}