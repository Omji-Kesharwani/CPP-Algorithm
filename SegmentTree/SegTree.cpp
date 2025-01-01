#include<bits/stdc++.h>
using namespace std;

vector<int>A,ST;
void build(int node,int L,int R)
{
  if(L==R)
  {
    ST[node]=A[L];
  }
  else{
    int mid=(L+R)/2;

    build(2*node,L,mid);
    build(2*node+1,mid+1,R);

    ST[node]=ST[2*node]+ST[2*node+1];
  }
}
void update(int node,int L,int R,int idx,int val)
{
  if(L==R)
  {
    A[idx]+=val;
    ST[node]+=val;
  }
  else{
    int mid=(L+R)/2;
    if(idx>=L and idx<=mid)
    {
      update(2*node,L,mid,idx,val);
    }
    else{
      update(2*node+1,mid+1,R,idx,val);
    }
    ST[node]=ST[2*node]+ST[2*node+1];
  }
}
int query(int node,int tl,int tr,int l,int r)
{
  if(r<tl or tr<l)
  return 0;
  if(l<=tl and tr<=r)
  return ST[node];
  int tm=(tl+tr)/2;

  return query(2*node,tl,tm,l,r)+query(2*node+1,tm+1,tr,l,r);
}
int main()
{
  int n = 6;
    A = { 0, 1, 3, 5, -2, 3 };

    // Create a segment tree of size 4*n
    ST.resize(4 * n);

    // Build a segment tree
    build(1, 0, n - 1);
    cout << "Sum of values in range 0-4 are: "
         << query(1, 0, n - 1, 0, 4) << "\n";

    // Update the value at idx = 1 by
    // 100 thus becoming 101
    update(1, 0, n - 1, 1, 100);
    cout << "Value at index 1 increased by 100\n";
    cout << "sum of value in range 1-3 are: "
         << query(1, 0, n - 1, 1, 3) << "\n";

    return 0;

}