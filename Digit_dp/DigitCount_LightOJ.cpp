#include <bits/stdc++.h>
using namespace std;
#define int long long
int dp[12][12];// index , previous digit
int solve(vector<int>&arr,int idx,int prev,int n)
{
  if(idx==n)
  {
    return 1;
  }
  if(dp[idx][prev]!=-1)
  {
    return dp[idx][prev];
  }
  int ans=0;
  for(int i=0;i<arr.size();i++)
  {
    if(prev==0 || abs(arr[i]-prev)<=2 ){
      ans+=solve(arr,idx+1,arr[i],n);
    }
  }
  return dp[idx][prev]=ans;
}
int32_t main()
{
int m,n;
cin>>m>>n;
vector<int>arr(m);
for(auto &x:arr)
{
  cin>>x;
}
memset(dp,-1,sizeof(dp));
cout<<solve(arr,0,0,n);
}