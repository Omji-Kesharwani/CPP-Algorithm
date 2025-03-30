//Beny and the broken odometer
#include <bits/stdc++.h>
using namespace std;
#define int long long
int dp[12][2][2];
int solve(string& s,int idx,int tight,int flag)
{
  if(idx==s.size()) return flag;
  if(dp[idx][tight][flag]!=-1) return dp[idx][tight][flag];

  int limit=(tight==1)?s[idx]-'0':9;
  int ans=0;
  for(int i=0;i<=limit;i++)
  {
    int updateFlag=(flag || (i==3));
    ans+=solve(s,idx+1,(tight &&(i==s[idx]-'0')),updateFlag);
  }
  return dp[idx][tight][flag]=ans;
}

int32_t main()
{
int n;
cin>>n;
 string s=to_string(n);
 memset(dp,-1,sizeof(dp));
 int cntof3=solve(s,0,1,0);
 cout<<n-cntof3<<endl; 
    return 0;
}