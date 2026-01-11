struct FenwickTree{
  int n;
  vector<long long > bit ;
   FenwickTree(int n){
     this->n= n;
     bit.assign(n+1,0);
   }

   void update(int idx , long long delta)
   {
    while(idx <= n)
    {
      bit[idx] += delta;
      idx += idx & (-idx);
    }
   }

   long long  query(int idx )
   {
    long long sum =0;
    while(idx >0 )
    {
      sum += bit[idx];
      idx -= idx & (-idx);

    }
    return sum;
   }
   long long rangeQuery(int l,int r)
   {
    return query(r) - query(l-1);
   }
};

// Building the Fenwick Tree 
/*Option 1 : Updating one by one (simple)
for(int i=1;i<=n;ii)
{
  fenwick.update(i,arr[i]);
}

Option2 : Faster build 

for(int i=1;i<=n;i++)
{
 bit[i] += A[i];
 int j = i + (i & (-i));
 if(j<=n)
  bit[j] += bit[i];
 }