#include<bits/stdc++.h>
using namespace std;

vector<int>parent,rank,len;
int comp_count,max_size;
int find(int x)
{
  if(x==parent[x])
  return x;

  return parent[x]=find(parent[x]);
}

void merge(int x,int y)
{
  int lx = find(x);
  int ly = find(y);
  if(lx != ly)
  {
    if(rank[lx]<rank[ly])
    {
      parent[lx]=ly;
      len[ly]+=len[lx];
    }
    else if(rank[lx]>rank[ly])
    {
      parent[ly]=lx;
      len[lx]+=len[ly];
    }
    else
    {
      parent[lx]=ly;
      rank[ly]++;
      len[ly]+=len[lx];
  }

  comp_count--;
  max_size = max(max_size,max(len[lx],len[ly]));
}
}

int main()
{
  ios::sync_with_stdio(false);
  cin.tie(0);

  int n,m;
  cin>>n>>m;
  parent.resize(n+1);
  rank.resize(n+1,0);
  len.resize(n+1,1);

  for(int i=1;i<=n;i++) parent[i] = i;

  comp_count = n;
  max_size = 1;

  for(int i=0;i<m;i++)
  {
    int u,v;
    cin>>u>>v;
    merge(u,v);
    cout<<comp_count<<" "<<max_size<<endl;
  }
}