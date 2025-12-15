//Subset Partition dp
/*
Question : There are N rabbits numbered from 1 .. N .For each i,j , the compatibility of rabbit i and rabbit j is given by A[i][j] . also A[i][j] = A[j][i]. , A[i][i] = 0.Divide them into some groups such that each rabbit belongs to only one grp .Taro earns A[i][j] points if rabbit i and rabbit j are in the same group .Find the maximum points Taro can earn .

|A[i][j]| < 10^9
1<= N <= 16
*/

/*
Approach :
 dp[mask] = maximum score achievable by grouping rabbits represented by mask
Meaning : mask represents the rabbits already grouped 

Base case :
dp[0] = 0 , the rabbits are not grouped yet therfore the score is 0.

We first compute the groupScore 
groupScore[mask] = total compatibility inside this subset 

*/

#include<bits/stdc++.h>
using namespace std;
using ll =  long long ; 
int main()
{
  ios::sync_with_stdio(false);
  cin.tie(0);

  int n;
  cin>>n;

  vector<vector<ll>>a(n,vector<ll>(n));

  for(int i=0;i<n;i++)
  {
    for(int j=0;j<n;j++)
    {
      cin>>a[i][j];
    }
  }

  int FULL = 1<<n;

  // Precompute the score of each subset 

  vector<ll>groupScore(FULL,0);

  for(int mask =0;mask <FULL;mask++)
  {
    ll sum =0;
    for(int i=0;i<n;i++)
    {
      if(!(mask & (1<<i))) continue;

      for(int j =i+1;j<n;j++)
      {
        if(mask & (1<<j))
        {
          sum += a[i][j]; 
        }
      }
    }

    groupScore[mask] = sum ;
  }

  // DP over the subsets
  vector<ll>dp(FULL,LLONG_MIN);
  dp[0]=0;
  for(int mask = 1;mask<FULL ;mask++)
  {
    for(int sub = mask ; sub>0 ; sub = (sub-1) & mask )
    {
       dp[mask] = max(dp[mask] , dp[mask ^ sub] + groupScore[sub]);
    }
  }

  cout<<dp[FULL-1]<<endl;
  return 0;

}