#include<bits/stdc++.h>
using namespace std;
int n;
vector<int>bit;
void update(int id,int val)
{
  while(id<=n)
  {
    bit[id]+=val;
    id+=(id & -id);
  }
}
int query(int id)
{
  int ans=0;
  while(id>0)
  {
    ans+=bit[id];
    id-=(id & -id);
  }
  return ans;
}