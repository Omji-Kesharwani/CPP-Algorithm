#include<bits/stdc++.h>
using namespace std;
#define int long long
int dp[10][2][80];// index, tight, sum
bool isPrime(int n)
{
  if(n<=1)
  {
    return false;
  }
  for(int i=2;i*i<=n;i++)
  {
    if(n%i==0)
    {
      return false;
    }
  }
  return true;
}
int solve(string& s,int idx,int tight,int sum)
{
  if(idx==s.size())
  {
    if(isPrime(sum))
    {
      return 1;
    }
    else
    {
      return 0;
    }
  }
  if(dp[idx][tight][sum]!=-1)
  {
    return dp[idx][tight][sum];
  }
  int limit=(tight==1)?s[idx]-'0':9;
  int ans=0;
  for(int i=0;i<=limit;i++)
  {
    int updateSum=sum+i;
    ans+=solve(s,idx+1,(tight &&(i==s[idx]-'0')),updateSum);
  }
   
  return dp[idx][tight][sum]=ans;
}
int32_t main()
{
  int l,r;
  cin>>l>>r;
  string ri=to_string(r);
  memset(dp,-1,sizeof(dp));
  int rightAns=solve(ri,0,1,0);
  memset(dp,-1,sizeof(dp));
  string le=to_string(l-1);
  int leftAns=solve(le,0,1,0);
  cout<<rightAns-leftAns<<endl;
    return 0;
}