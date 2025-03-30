#include <iostream>
#include<bits/stdc++.h>
using namespace std;
class FenwickTree{
  public:
  vector<int>fen;
  public:
  FenwickTree(int N)
  {
    fen.resize(N);
  }
  void update(int i ,int add,int n)
  {
    while(i<n)
    {
      fen[i]+=add;
      i+=(i&(-i));
    }
  }
  int sum(int i)
  {
    int s=0;
   while(i>0)
   {
    s+=fen[i];
    i=i-(i&(-i));
   }
   return s;
  }
  int rangeSum(int l,int r)
  {
    return sum(r)-sum(l-1);
  }
};
int main()
{
    
    return 0;
}