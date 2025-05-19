#include<bits/stdc++.h>
using namespace std;
#define ll long long

int n,l;
//n-->no. of nodes in the tree l-->level at which we want to find LCA.

vector<vector<int>>adj;
//adj--> to represent the adjacency matrix of a given tree.

int timer ;
//timer--> to calculate the time for the in and out of each node in the tree.

vector<int>tin,tout;
//tin-->to store the tin value of each node in the tree. tout-->to store the tout value of each node in the tree.


// dfs function

void dfs(int node,int par)
{
  tin[node]=++timer;
  // up[node][0] represents the immediate parent of the node 
  up[node][0]=par;
  for(int i=1;i<=l;i++)
  {
    up[node][i]=up[up[node][i-1]][i-1];
  }

  for(auto neighbor:adj[node])
  {
    // to avoid the back edge in a given tree. 			{				dfs(neighbor,node);			}
    if(neighbor!=par) 
    dfs(neighbor,node);
  }

  tout[node]=++timer;
}

bool is_ancestor(int node1,int node2)
{
  return tin[node1]<=tin[node2]  && tout[node1]>=tout[node2];
}


int lca(int node1,int node2)
{
  if(is_ancestor(node1,node2))
  return node1;
  if(is_ancestor(node2,node1))
  return node2;
  for(int i=l ;i>=0;--i)
  {
    if(!is_ancestor(up[u][i],v))
    u=up[u][i];
  }

  return up[u][0];
}
void preprocess(int root)
{
  tin.resize(n);
  tout.resize(n);
  timer=0;
  l=ceil(log2(n));
  up.assign(n,vector<int>(1+l));
  dfs(root,root);
}