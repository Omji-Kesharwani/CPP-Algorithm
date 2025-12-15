/*
Question: There are n people who wan to go to the top of the buiding which has only one elevator .You know the weight of each person and the maximum weight in the elevator .
What is the minimum number of elevator rides ?

*/

/*
Approach:
dp[mask]= (rides,last_weight)

where 
-rides : minimum number of rides needed for this subset 
-last-weight : total weight of people in the current (last) ride for this subset .

Base case : dp[0] = (1,0)

We have two cases :
1. Person fits in the current(last) ride 
if last_weight+w[i] <= x:
newMask = mask | (1<<i)
dp[newMask] = (rides,last_weight+w[i])

2. Person does not fit in the current ride
newMask = mask | (1<<i)
dp[newMask] = (rides+1, w[i])
*/

#include<bits/stdc++.h>
using namespace std;

int main()
{
  ios::sync_with_stdio(false);
  cin.tie(0);

  int n;
  long long x ; // the weight the lift can take in one ride 
  cin>>n>>x;

  vector<long long> w(n);
  for(int i=0;i<n;i++)
    cin>>w[i];

    int N = 1<<n;
    const long long INF = 1e18;

    vector<pair<long long,long long>>dp(N,{INF,INF});

    dp[0] = {1,0};

    for(int mask=0;mask<N;mask++)
    {
      auto [rides,last_w] = dp[mask];
      if(rides ==INF)
      continue;
      for(int i=0;i<n;i++)
      {
        if(mask & (1<<i)) continue;
        int newMask = mask | (1<<i);
        pair<long long,long long> candidate;

        if(last_w + w[i] <= x)
       {
          candidate = {rides,last_w+w[i]};
       }
        else
        {
          candidate = {rides+1,w[i]};
        }

        dp[newMask] = min(dp[newMask],candidate);
      }
    }

    int fullMask = N-1;
    cout<<dp[fullMask].first<<"\n";
    return 0;
  }

   