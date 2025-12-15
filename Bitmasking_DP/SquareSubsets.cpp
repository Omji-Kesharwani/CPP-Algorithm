/*
Question : Count the number of subsets of a given array such the product of subarray of elements of the array is a square number .
note the value of element in the array is upto 70

dp[mask] = number of ways to choose a subset from the values we have processed so far such that the xor of the xor of their masks is exactly 'mask'.


Initially , before processing anything there is exactly one subset : the empty subset ,with XOR  = 0 ;

So:
dp[0]=1
dp[others] = 0 

Now , move from each v from 1 to 70 with cnt[v] =c>0;
1.Compute mv = mask[v]
2.Compute :
 evenWays = powermod(2,c-1)
 oddWays =powermod(2,c-1)

 Create a DP arry next_dp[mask] initially 0.

 Transition with each mask :
 If we take an even number of v's , XOR does not change :
 next_dp[mask] += dp[mask] * evenWays

 If we take an odd number of v's , XOR flips by mv :
 next_dp[mask ^ mv] += dp[mask] * oddWays
*/

#include<bits/stdc++.h>
using namespace std ;

const long long MOD = 1e9+7;

long long modPow(long long base,long long exp)
{
  long long res =1;
  base %= MOD ;
  while(exp>0)
  {
    if (exp&1)
    {
      res = (res*base)%MOD;
    }
    base = (base*base)%MOD;
    exp >>=1;
  }

  return res ;
}

int main()
{
  ios::sync_with_stdio(false);
  cin.tie(0) ;

  int n;
  cin>>n;

  vector<int>a(n);
  for(int i=0;i<n;i++)
  {
    cin>>a[i];
  }

  // Step 1 : list of primes upto 70
  vector<list>primes ={
    2,3,5,7,11,13,17,19,23,29,31,37,41,43,47,53,59,61,67
  };

  int P = (int)primes.size();
  int MAXMASK = 1<<P ;
  // step 2 : precompute mask for each v in [1..70]
  int valMask[71];
  for(int v =1 ;v<=70;v++)
  {
    int x =v;
    int mask = 0 ;
    for(int i=0;i<P;i++)
    {
      int p = primes[i];
      int cnt =0;
      while(x%p==0)
      {
        x/=p;
        cnt^=1; // toggle parity
      }
      if(cnt & 1)
      {
        mask |= (1<<i);
      }
    }
    valMask[v] = mask;
  }

  //Step 3 : Count occurrences of each value 

  int cnt[71]={0};
  for(int i=0;i<n;i++)
  {
    cnt[a[i]]++;
  }

  // Step 4 : DP over mask
  vector<long long> dp(MAXMASK,0) ,next_dp(MAXMASK);

  dp[0] = 1 ; // empty subset

  //Process each value from 1 to 70
  for(int v =1 ;v<=70;v++)
  {
    int c =cnt[v];
    if(c==0) continue;
    long long evenWays = modPow(2,c-1);
    long long oddWays = evenWays ;
    int mv = valMask[v];
    fill(next_dp.begin(),next_dp.end(),0);

    for(int mask =0;mask<MAXMASK;mask++)
    {
      if(dp[mask]==0) continue;
      long long cur =dp[mask];
      // pick even number of v's :XOR unchanged 
      long long addEven = (cur * evenWays)%MOD;
      next_dp[mask] = (next_dp[mask] + addEven)%MOD;

      // pick odd number of v's : XOR flips by mv

      long long addOdd = (cur * oddWays)%MOD;
      next_dp[mask^mv] = (next_dp[mask^mv] + addOdd)%MOD;

    }
    dp.swap(next_dp);
  }
 // dp[0] = number of subsets whose product is a perfect sqaure 
 long long ans = dp[0]-1;//exclude empty set
 if(ans <0 ) ans +=MOD;
 cout<<ans % MOD<<endl;
}