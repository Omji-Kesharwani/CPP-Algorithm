#include<bits/stdc++.h>
using namespace std;
vector<int>segTree;
void build(vector<int>& arr ,int start,int end,int index)
{
  // time complexity --> O(nlogn)
 if(start==end)
 {
  segTree[index]=arr[start];
  return;
 }

 int mid=(start+end)/2;
 int left=2*index,right=2*index+1;
 build(arr,start,mid,left);
 build(arr,mid+1,end,right);
 segTree[index]=segTree[left]+segTree[right];
}
void update(vector<int>& arr ,int start,int end,int index,int pos,int value)
{
  // time complexity-->O(2*logn)==O(logn)
  if(start==end)
  {
  arr[pos]=value;
  segTree[index]=arr[pos];
  return;
  }
  int mid=(start+end)/2;
  if(mid>=pos)
  update(arr,start,mid,2*index,pos,value);
  else 
  update(arr,mid+1,end,2*index+1,pos,value);
  segTree[index]=segTree[2*index+1]+segTree[2*index];
}
int query(int start,int end,int index ,int l, int r)
{
  // time complexity -->O(log n)

  // complete overlap
  if(l>=start && end<=r)
  return segTree[index];

  // disjoint
  if(l>end || r<start)
  return 0;
  int mid=(start+end)/2;
  int leftAnswer=query(start,mid,2*index,l,r);
  int rightAnswer=query(mid+1,end,2*index+1,l,r);
 return leftAnswer+rightAnswer;

}
void debug(vector<int> a)
{
   for (int i = 1; i < a.size(); i++) {
    cout<< segTree[i] << " ";
  }
  cout<<endl;
}
void solve()
{
  int n;
  cin>>n;
  segTree.resize(2*n+1);
  vector<int>arr(n);
  for(auto &i:arr)
  cin>>i;
 build(arr,0,n-1,1);
  debug(segTree);
  debug(arr);
  // cout<<query(1,8,1,1,5)<<endl;
  // update(arr,0,n-1,1,1,3);
  // debug(segTree);
  // debug(arr);


}
int main()
{
solve();
}