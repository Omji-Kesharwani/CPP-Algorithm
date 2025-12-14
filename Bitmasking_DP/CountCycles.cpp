// Count the number of cycles in the graph

#include<bits/stdc++.h>
using namespace std;

long long dp [1<<19][19];
bool G[19][19];

int main()
{
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  int n,m;
  cin>>n>>m;

  for(int i=0;i<m;i++)
  {
    int a,b;
    cin>>a>>b;
    a--;
    b--;
    G[a][b]=1;
    G[b][a]=1;
  }

  long long ans =0;

  for(int start = 0; start < n;start++)
  {
    int  LIMIT = 1<<n;
    for(int mask = 0; mask < LIMIT ;mask++)
      for(int i=0;i<n;i++) dp[mask][i]=0;

    dp[1<<start][start]=1;

    for(int mask = 1<<start ;mask < LIMIT ;mask++)
    {
      if(!(mask &(1<<start))) continue;

      for(int u=0;u<n;u++)
      {
        if(!(mask & (1<<u))) continue; // u must be in mask 
        long long ways = dp[mask][u];

        if(!ways) continue;

       

        if(__builtin_popcount(mask) >= 3 && G[u][start])
        {
          ans += ways;
        }
      }


    }
    
  }
  // Each cycle is counted twice (once per direction)
  cout<<ans/2<<endl;

}