//Our salesman is residing in Banglore city and is planning to visit a bunc of cities in India and then return back to Banglore , all by airplanes .
// Wee need your help in minimizing the total airfare .

//Solution Bitmask + Dp

#include<bits/stdc++.h>
using namespace std;

int main()
{
   ios::sync_with_stdio(false);
   cin.tie(0);
    
   int t;
   cin>>t;
   while(t--)
   {
    int n;
    cin>>n;
    int m = n+1; // total cities including Banglore
    vector<vector<long long >> cost(m,vector<long long >(m,0));
    for(int i=0;i<m;i++)
    {
        for(int j=0;j<m;j++)
        {
          if(i==j)
          {
            cost[i][j] = 0;
          }
          else
          {
            long long x;
            cin>>x;
            cost[i][j] = x;
          }
        }
    }

    // Bitmask Dp over cities (1..n)
    // mask : bits 0..n-1 represent the cities 1..n

    int FULL = (1<<n)-1;

    const long long INF = (long long) 1e18;
    vector<vector<long long>> dp(1<<n,vector<long long>(m,INF));

    //Base case : directly go from Banglore (0) to city u 

    for(int u=1;u<=n;u++)
    {
      int mask = 1<<(u-1);
      dp[mask][u] = cost[0][u];
    }
    
    //Transitions

    for(int mask = 0 ;mask <= FULL ; mask++)
    {
      for(int u=1;u<=n;u++)
      {
        // u must be included in the mask as the last visited city
        if(!(mask & (1<<(u-1)))) continue;

        long long cur = dp[mask][u];
        if(cur==INF) continue; // the node u is not reachable 

        for(int v=1;v<=n;v++)
        {
          if(mask & (1<<(v-1))) // node v is already visited 
          continue;
         
          int newMask = mask | (1<<(v-1));

          long long newcost = cur + cost[u][v];

          dp[newMask][v]=min(dp[newMask][v],newcost);

        }


      }
    }
    // now we have visited all the cities from 1..n
    //Return from each possible last city  u to Banglore (0)

    long long ans = INF;
    for(int u=1;u<=n;u++)
    {
      long long tourCost = dp[FULL][u] + cost[u][0];
      ans = min(ans,tourCost);
    }

    cout<<ans<<endl;
   }
}

