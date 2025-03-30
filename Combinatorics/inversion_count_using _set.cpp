#include <iostream>
#include<bits/stdc++.h>
using namespace std;
long long getInvCount(int arr[],int n)
{
  multiset<int> set1;
  set1.insert(arr[0]);
  long long invcount=0;
  multiset<int>::iterator itset1;
  for(int i=1;i<n;i++)
  {
    set1.insert(arr[i]);
    itset1=set1.upper_bound(arr[i]);
    invcount+=distance(itset1,set1.end());
  }
  return invcount;
}
int main()
{
    
    return 0;
}