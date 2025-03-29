#include<bits/stdc++.h>
using namespace std;
#define int long long
int dp[20][2][20];
int  solve(string& s,int idx,int tight,int cnt)
{
  if(idx==s.size())
  {
    return cnt;
  }
  if(dp[idx][tight][cnt]!=-1)
  {
    return dp[idx][tight][cnt];
  }
  int ans=0;
  int limit=(tight==1)?s[idx]-'0':9;
  for(int i=0;i<=limit;i++)
  {
    ans+=solve(s,idx+1,(tight&(i==s[idx]-'0')),cnt+(i==3));
  }
  return dp[idx][tight][cnt]=ans;
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