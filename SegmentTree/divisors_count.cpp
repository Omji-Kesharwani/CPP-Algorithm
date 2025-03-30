#include <iostream>
#include<bits/stdc++.h>
using namespace std;
const int N=1e7+10;
vector<bool>isPrime(N,1);
vector<int>lp(N,0),hp(N,0);
int main()
{
    isPrime[0]=isPrime[1]=false;
    //n(loglogN)
    for(int i=2;i<N;i++)
    {
      if(isPrime[i]==true)
      {
        lp[i]=hp[i]=i;
        for(int j=2*i;j<N;j+=i)
        {
          isPrime[j]=false;
          hp[j]=i;
          if(lp[j]==0)
          {
            lp[j]=i;
          }
        }
      }
    }
    int num;
    cin>>num;
    map<int,int>prime_factors;
    while(num>1)
    {
      int prime_factor=hp[num];
      while(num%prime_factor==0)
      {
        num/=prime_factor;
        prime_factors[prime_factor]++;
      }
    }
    int count_divisors=0;
    for(auto& prime:prime_factors)
    {
      cout<<prime.first<<" ";
    count_divisors+=prime.second+1;
    }
    cout<<endl;
    cout<<count_divisors<<endl;
    return 0;
}