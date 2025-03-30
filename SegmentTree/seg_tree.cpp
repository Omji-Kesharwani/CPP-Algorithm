#include <iostream>

#include<bits/stdc++.h>
using namespace std;

// class SGTtree{
//   public:
//   vector<int>seg;
//   SGTtree(int n){
//  seg.resize(4*n+1);
//   }
// void build(int ind,int low,int high,int arr[]){
//   if(low==high)
//   {
//     seg[ind]=arr[low];
//     return ;
//   }
//  int mid=(low+high)/2;
//  build(2*ind+1,low,mid,arr);
//  build(2*ind+2,mid+1,high,arr);
//  seg[ind]=min(seg[2*ind+1],seg[2*ind+2]);

// }

// int query(int ind,int low,int high,int l,int r)
// {
//   // no overlap
// if(r<low ||high<l) return INT_MAX;
// if(low>=l && high<=r) return seg[ind];
// int mid=(low+high)>>1;
// int left=query(2*ind+1,low,mid,l,r);
// int right=query(2*ind+2,mid+1,high,l,r);
// return min(left,right);
// }

// void update(int ind,int low,int high,int i,int val){
// if(low==high)
// {
//   seg[ind]=val;
//   return;
// }
// int mid=(low+high)>>1;
// if(i<=mid)
// {
//   update(2*ind+1,low,mid,i,val);
// }
// else{
//   update(2*ind+2,mid+1,high,i,val);
// }
// seg[ind]=min(seg[2*ind+1],seg[2*ind+2]);
// }
// };


// class info{
//   public:
// int open,close,full;
// public:
// info(int _open,int _close,int _full)
// { 
//   open=_open;
//   close=_close;
//   full=_full;
// }
// info(){
//   open=0;
//   close=0;
//   full=0;
// }
// };
// info merge(info left,info right)
// {
//   info ans =info(0,0,0);
//   ans.full=left.full+right.full+min(left.open,right.close);
//   ans.open=left.open+right.open-min(left.open,right.close);
//   ans.close=left.close+right.close-min(left.open,right.close);
//   return ans;
// }
// void build(int ind,int low,int high,string s ,info seg[])
// {
//   if(low==high)
//   {
//     seg[ind]=info(s[low]=='(',s[low]==')',0);
//     return;
//   }
//   int mid=(low+high)/2;
//   build(2*ind+1,low,mid,s,seg);
//   build(2*ind+2,mid+1,high,s,seg);
//   seg[ind]=merge(seg[2*ind+1],seg[2*ind+2]);
// }
// info query(int ind,int low ,int high,int l ,int r,info seg[]){
//  if(r<low || high<l)
//  return info();
//  if(low>=l && high<=r)
//  return seg[ind];
//  int mid=(low+high)>>1;
//  info left=query(2*ind+1,low,mid,l,r,seg);
//  info right=query(2*ind+2,mid+1,high,l,r,seg);
//  return merge(left,right);
// }
// void solve4(){
// string s;
// cin>>s;
// int n=s.length();
// info seg[4*n];
// build(0,0,n-1,s,seg);
// int q;
// cin>>q;
// while(q--){
//   int l,r;
//   cin>>l>>r;
//   l--;
//   r--;
//   info ans=query(0,0,n-1,l,r,seg);
//   cout<<ans.full*2<<endl;
// }
//}

class SGTtree{
  public:
  vector<int>seg;
  SGTtree(int n){
 seg.resize(4*n+1);
  }
void build(int ind,int low,int high,int arr[]){
  if(low==high)
  {
    seg[ind]=arr[low];
    return ;
  }
 int mid=(low+high)/2;
 build(2*ind+1,low,mid,arr);
 build(2*ind+2,mid+1,high,arr);
 seg[ind]=seg[2*ind+1]+seg[2*ind+2];

}

int query(int ind,int low,int high,int l,int r)
{
  // no overlap
if(r<low ||high<l) return 0;
if(low>=l && high<=r) return seg[ind];
int mid=(low+high)>>1;
int left=query(2*ind+1,low,mid,l,r);
int right=query(2*ind+2,mid+1,high,l,r);
return left+right;
}

void update(int ind,int low,int high,int i,int val){
if(low==high)
{
  seg[ind]=val;
  return;
}
int mid=(low+high)>>1;
if(i<=mid)
{
  update(2*ind+1,low,mid,i,val);
}
else{
  update(2*ind+2,mid+1,high,i,val);
}
seg[ind]=(seg[2*ind+1]+seg[2*ind+2]);
}
};
void solve5(){
  int n;
  cin>>n;
  int arr[n];
  int mx=-1;
  for(int i=0;i<n;i++)
  {
    cin>>arr[i];
    mx=max(mx,arr[i]);
  }
  mx+=1;
  int freq[mx]={0};
  for(int i=0;i<n;i++)
  {
    freq[arr[i]]++;
  }
  SGTtree st(mx);
  st.build(0,0,mx-1,freq);
  int cnt=0;
  for(int i=0;i<n;i++)
  {
    freq[arr[i]]--;
    st.update(0,0,mx-1,arr[i],-1);
    cnt+=st.query(0,0,mx-1,1,arr[i]-1);
  }
  cout<<cnt<<endl;
}
int main(){
  int t;
  cin>>t;
  while(t--)
  {
 solve5();
  }
 
  return 0;
}