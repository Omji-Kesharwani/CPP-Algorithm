/*
A game on an undirected graph is played by two players, Mouse and Cat, who alternate turns.

The graph is given as follows: graph[a] is a list of all nodes b such that ab is an edge of the graph.

The mouse starts at node 1 and goes first, the cat starts at node 2 and goes second, and there is a hole at node 0.

During each player's turn, they must travel along one edge of the graph that meets where they are.  For example, if the Mouse is at node 1, it must travel to any node in graph[1].

Additionally, it is not allowed for the Cat to travel to the Hole (node 0).

Then, the game can end in three ways:

If ever the Cat occupies the same node as the Mouse, the Cat wins.
If ever the Mouse reaches the Hole, the Mouse wins.
If ever a position is repeated (i.e., the players are in the same position as a previous turn, and it is the same player's turn to move), the game is a draw.
Given a graph, and assuming both players play optimally, return

1 if the mouse wins the game,
2 if the cat wins the game, or
0 if the game is a draw.

Input: graph = [[2,5],[3],[0,4,5],[1,4,5],[2,3],[0,2,3]]
Output: 0

*/

class Solution {
public:
    int catMouseGame(vector<vector<int>>& graph) {
        int n = graph.size();
        /*
        state[mouse position][cat position][whose turn ]
        */
        vector<vector<vector<int>>> state(n,vector<vector<int>>(n,vector<int>(2,0)));
        /*
        indegree[mouse position][cat position][whose turn (cat or mouse)] = number of paths we can go to         from the current state of whose the current turn is .
        */
        vector<vector<vector<int>>>indegree(n,vector<vector<int>>(n,vector<int>(2,0)));
        /*
          queue(mouse position , cat position, whose turn , result )
        */
          queue<tuple<int,int,int,int>>q;

        for(int i=0;i<n;i++)
        {
            // This condition is checked since cat can not go to the hole 
            if(i!=0)
            {
            // initially all the states in which the mouse position is equals the hole position which is equal to  0 , then it does not depends upon the whose turn , mouse will always wins and push in the queue.    
            state[0][i][0] = state[0][i][1] = 1;
            q.emplace(0,i,0,1);
            q.emplace(0,i,1,1);

          // initially all the states in which the mouse position is equals to the cat position then the cat will always wins .
            state[i][i][0] = state[i][i][1] = 2;
            q.emplace(i,i,0,2);
            q.emplace(i,i,1,2);

            }
          // initialization is done for indegree vector
            for(int j=0;j<n;j++)
            {
                indegree[i][j][0] = graph[i].size();
                indegree[i][j][1] = graph[j].size();
                // this condition remove the 0 in the traverse position if it is cat's turn 
                if(find(graph[j].begin(),graph[j].end(),0)!=graph[j].end())
                {
                    --indegree[i][j][1];
                }
            }
        }

        while(!q.empty())
        {
            // pop the first element from the queue 
            auto [cur_mos_pos,cur_cat_pos,cur_turn,result] =q.front();
            q.pop();
            // check for whose the current turn is 
            int nextTurn = 1- cur_turn;
            // if it's the mouse turn then
            if(nextTurn == 0)
            {
                // check for all the position to where the mouse can go from this position 
                for(int next_mos_pos : graph[cur_mos_pos])
                {
                    // if this state is not processed before 
                    if(state[next_mos_pos][cur_cat_pos][nextTurn]==0)
                    {
                        // if the previously the mouse wins then again the mouse wins 
                        if(result==1)
                        {
                            state[next_mos_pos][cur_cat_pos][nextTurn]=1;
                            q.emplace(next_mos_pos,cur_cat_pos,nextTurn,1);
                        }
                        else{
                         // else checks for if there is path left or not 
                         // if not then the cat will be forced to win the game
                            if(--indegree[next_mos_pos][cur_cat_pos][nextTurn]==0)
                            {
                                state[next_mos_pos][cur_cat_pos][nextTurn]=2;
                                q.emplace(next_mos_pos,cur_cat_pos,nextTurn,2);
                            }
                        }
                    }
                }
            }
            // if its the cat turn then,
            else{
                // check all  the positions the cat can traverse from the current cat position
                 for(int next_cat_pos : graph[cur_cat_pos])
                 {
                    if(next_cat_pos == 0) continue ;
                    if(state[cur_mos_pos][next_cat_pos][nextTurn]==0)
                    {
                        if(result == 2)
                        {
                            state[cur_mos_pos][next_cat_pos][nextTurn]=2;
                            q.emplace(cur_mos_pos,next_cat_pos,nextTurn,2);
                        }
                        else{
                            if(--indegree[cur_mos_pos][next_cat_pos][nextTurn]==0)
                            {
                                state[cur_mos_pos][next_cat_pos][nextTurn]=1;
                                q.emplace(cur_mos_pos,next_cat_pos,nextTurn,1);
                            }
                        }
                    }
                 }
            }
        }
            // this state simply states that if mouse was at 1 position and the cat is at 2nd position and its the mouse turn
        return state[1][2][0];

    }
};