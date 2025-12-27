//Leetcode --> 943. Find the Shortest Superstring
// INF +INF < INT_MAX
#define INF 0x3f3f3f3f
class Solution {
public:
/*
  VISITED_ALL = it contains the mask of the all strings visited (i.e 1<<n )
  n -> number of strings in the array
  dist -> stores the number of additional characters appends to transform from one string to the other 
  path -> used for reconstructing the ans as path[mask][pos] = best index of the string to which we can traverse
  dp[mask][pos] ->  stores the min length of the string while starting from pos and make all the string visited
*/
   int VISITED_ALL ,n;
   vector<vector<int>> dist ,path,dp;
    int calcDist(string a,string b) // calculate the additional character required to concatenate the string b to the end of a string
    {
        // check all the suffix of the a string is present as the prefix in the string b
        // str.rfind(x,0) -> checks whether the string x is present as the prefix in the string str and return theindex of the substring
        for(int i=0 ; i<a.length() ;i++)
        {
           if(b.rfind(a.substr(i),0)==0)
            return b.length()-(a.length()-i);
        }
       // if prefix is not matched then we have to append all the characters of b to the end of a
        return b.length();
    }
    // initially mask has the value of 1<<k and pos is k
    int tsp(int mask,int pos) // calculates the ans starting from the pos and make all the string visited
    {
        if(mask == VISITED_ALL)
         return 0;

        if(dp[mask][pos]!=-1)
        {
            return dp[mask][pos];
        }

        int ans = INF ,best;// ans stores the minimum possible extra characters to append 

        for(int city =0; city < n;city++) // visiting every string and check which is not yet visited or calculated 
        {
            if((mask & (1<<city)) == 0)
            {
                int result = dist[pos][city] + tsp(mask |(1<<city),city);
                if(result < ans)
                {
                    ans = result;
                    best =city;// for recovering the path
                }
            }
        }


        path[mask][pos] = best; // stores the best index of the string to which we can traverse
        return dp[mask][pos] = ans ; // calculates the minimum possible extra characters to append


    }

    string constructPath(vector<string>& word,int k)
    {
        int curr = k; //starting from the starting node 
        string result = word[k];
        int mask = (1<<k);
        int child = path[mask][k]; // get the node to which we have to traverse next from the current node
        while(child !=-1)
        {
            result += word[child].substr(word[child].length()-dist[curr][child]);
            mask |= (1<<child);
            curr = child;
            child = path[mask][child];
        }

        return result;
    }
    string shortestSuperstring(vector<string>& words) {
       n = words.size();
       VISITED_ALL =(1<<n)-1;
       dist.assign(n,vector<int>(n,0));

       //calculates the additional characters required to transform from one string to the other
       for(int i=0;i<n;i++)
       {
        for(int j=0;j<n;j++)
        {
            if(i==j) dist[i][j] =0;
            else
            {
                dist[i][j]=calcDist(words[i],words[j]);
            }
        }
       }

       int ansLen  = INF;
       string ans ;
       // starting from every string and make all the string visited
       for(int k=0;k<n;k++)
       {
          path.assign((1<<n),vector<int>(n,-1));
          dp.assign((1<<n),vector<int>(n,-1));
          tsp(1<<k,k);
          string result = constructPath(words,k);
          if(result.length() < ansLen)
          {
            ans = result;
            ansLen = result.length();
          }
       }  

       return ans;
    }
};