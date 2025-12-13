#include<bits/stdc++.h>
using namespace std;

// Knight Tour Problem

const int N = 8;
int dx[8] = {2,1,-1,-2,-2,-1,1,2};
int dy[8] = {1,2,2,1,-1,-2,-2,-1};

inline bool inside(int x,int y)
{
  return x>=0 && x<N && y>=0 && y<N;
}

int countMoves(int x,int y,vector<vector<int>>&board)
{
  int cnt = 0;
  for(int k=0;k<8;k++)
  {
    int nx = x+dx[k];
    int ny = y+dy[k];
    if(inside(nx,ny) && board[nx][ny]==0)
      cnt++;
  }
  return cnt;
}
//DFS with Warndorff ordering 
bool dfs(int x,int y,int step,vector<vector<int>>&board)
{
  board[x][y]=step;
  if(step==N*N)
    return true;

  // collect the candidates and sort them by onward moves (Warndorff)
  vector<pair<int,pair<int,int>>>cand ;// (deg,(nx,ny))

  cand.reserve(8);

  for(int k=0;k<8;k++)
  {
    int nx = x+dx[k];
    int ny = y+dy[k];
    if(inside(nx,ny) && board[nx][ny]==0)
    {
      int deg = countMoves(nx,ny,board);
      cand.push_back({deg,{nx,ny}});
    }
  }

  sort(cand.begin(),cand.end());

  for(auto &p :cand)
  {
    int nx = p.second.first;
    int ny = p.second.second;
    if(dfs(nx,ny,step+1,board)) return true ;
  }

  //backtrack
  board[x][y]=0;
  return false;

}

int main()
{
  ios::sync_with_stdio(false);
  cin.tie(0);
  int sx,sy;
  cin>>sx>>sy;
  sx--,sy--;
  vector<vector<int>>board(N,vector<int>(N,0));
  bool ok = dfs(sy,sx,1,board);
  if(!ok)
  {
    cout<<"No solution\n";
    return 0;
  }

  for(int i=0;i<N;i++)
  {
    for(int j=0;j<N;j++)
      {
        cout<<board[i][j]<<(j+1==N ?'\n':' ');
      }
  }
}