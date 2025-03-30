#include <iostream>
#include<bits/stdc++.h>
using namespace std;
// range sum query 
class ST{
  vector<int>st,lazy;
  public:
  ST(int n){
    st.resize(4*n);
    lazy.resize(4*n);
  }
  public:
  void build(int ind,int low,int high,int arr[])
  {
    if(low==high)
    {
      st[ind]=arr[low];
      return ;
    }
    int mid=(low+high)>>1;
    build(2*ind+1,low,mid,arr);
    build(2*ind+2,mid+1,high,arr);
    st[ind]=min(st[2*ind+1],st[2*ind+2]);
  }
  public:
  void update(int ind,int low,int high,int l,int r,int val)
  {
    //update the previous remaining updates and propogate downwards
    if(lazy[ind]!=0){
    st[ind]+=lazy[ind];
    //propogate the lazy update downwards for the remaining nodes to get updated
    if(low!=high)
    {
      lazy[2*ind+1]+=lazy[ind];
      lazy[2*ind+2]+=lazy[ind];
    }
    lazy[ind]=0;
    }
    // if there is no overlap
    if(high<l or  r<low)
    {
      return;
    }
    // complete overlap
    if(low>=l and high<=r)
    {
      st[ind]+=val;
      if(low!=high)
      {
        lazy[2*ind+1]+=val;
        lazy[2*ind+2]+=val;
      }
      return;
    }
    //partial overlap
    int mid=(low+high)>>1;
   update(2*ind+1,low,mid,l,r,val);
   update(2*ind+2,mid+1,high,l,r,val);
   st[ind]=min(st[2*ind+1],st[2*ind+2]);
  }
  public :
  int query(int ind,int low,int high,int l,int r )
  {
    //update if updates are remaining 
    //then update
     if(lazy[ind]!=0){
    st[ind]+=lazy[ind];
    //propogate the lazy update downwards for the remaining nodes to get updated
    if(low!=high)
    {
      lazy[2*ind+1]+=lazy[ind];
      lazy[2*ind+2]+=lazy[ind];
    }
    lazy[ind]=0;
    }
    //no overlap return 0
    if(high<l or r<low)
    return INT_MAX;
    // complete overlap
    if(low>= l and high<=r)
    {
      return st[ind];
    }
    //partial overlap
    int mid=(low+high)>>1;
    int left=query(2*ind+1,low,high,l,r);
    int right=query(2*ind+2,low,high,l,r);
    return min(left,right);
  }

};
int main()
{
  int n;
  cin>>n;
  int arr[n];
  for(int i=0;i<n;i++)cin>>arr[i];
  ST st(n);
  st.build(0,0,n-1,arr);
  int q;
  cin>>q;
  while(q--)
  {
    int type;
    cin>>type;
    if(type==1)
    {
     int l,r;
    cin>>l>>r;
  cout<<st.query(0,0,n-1,l,r);
    }
    else
    {
      int l,r,val;
      cin>>l>>r>>val;
      st.update(0,0,n-1,l,r,val);
    }

  }
    
    return 0;
}