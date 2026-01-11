/*
A company has n employees with certain salaries. Your task is to keep track of the salaries and process the queries .
The first input line contains two integers n and q , the number of employees and the number of queries.
The employees are numbered 1, 2, ..., n.
The next line contains n integers s1, s2, ..., sn, where si is the salary of the i-th employee.
After that, there are q lines describing the queries. Each query is of one of the following two types:
! k x: change the salary of the k-th employee to x.
? a b : count the number of employees whose salary is between a and b (inclusive).
*/

struct Fenwick{
  int n;
  vector<int>bit ;
  Fenwick(int n) : n(n), bit(n+1,0) {}
  void update(int idx,int val)
  {
    while(idx<=n)
    {
      bit[idx]+=val;
      idx+=idx&-idx;
    }
  }

  int query(int idx)
  {
    int sum=0;
    while(idx>0)
    {
      sum+=bit[idx];
      idx-=idx&-idx;
    }
    return sum;
  }
  int rangeQuery(int l,int r)
  {
    return query(r)-query(l-1);
  }
};

int main()
{
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  int n,q;
  cin>>n>>q;
  vector<int>p(n);
  for(int i=0;i<n;i++)
  {
    cin>>p[i];
  }
  vector<tuple<char,int,int>>queries;
  vector<int>values ;
  for(int x : p)
    values.push_back(x);

  for(int i=0;i<q;i++)
  {
    char type;
    cin>>type;
    if(type=='!')
    {
      int k, x;
      cin>>k>>x;
      queries.emplace_back({type,k-1,x});
      values.push_back(x);
    }
    else
    {
      int a,b;
      cin>>a>>b;
      queries.emplace_back({type,a,b});
      values.push_back(a);
      values.push_back(b);
    }
  }

  //Coordinate Compression
  sort(values.begin(),values.end());
  values.erase(unique(values.begin(),values.end()),values.end());

  auto getId = [&](int x){
    return lower_bound(values.begin(),values.end(),x)-values.begin()+1;
  };
  Fenwick fw(values.size());
  for(int i = 0;i<n;i++)
  {
    fw.update(getId(p[i]),1);
  }

  //Process queries
  for(auto& [type,k,x] : queries)
  {
    if(type=='!')
    {
      fw.update(getId(p[k]),-1);
      p[k]=x;
      fw.update(getId(p[k]),1);
    }
    else
    {
      int left = getId(k);
      int right = getId(x);
      cout<<fw.rangeQuery(left,right)<<'\n'
    }
  }
}