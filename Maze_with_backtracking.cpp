//A Maze is given as n*n matrix of blocks where source block is the upper left most block i.e., matrix[0][0] and destination block is lower rightmost block i.e., matrix[n-1][n-1]. A rat starts from source and has to reach the destination. The rat can move in only two directions: first forward if possible or down. If multiple solutions exist, the 
//longest earliest hop will be accepted. For the same hop distance at any point, forward will be preferred over downward. In the maze matrix, 0 means the block is the dead end and non-zero number means the block can be used in the path from source to destination. The non-zero value of mat[i][j] indicates number of maximum jumps rat can make from cell mat[i][j]. In this variation, Rat is allowed to jump multiple steps at a time instead of 1. Find a matrix which describes the position the rat to reach at the destination.
 

#include<bits/stdc++.h>
using namespace std;

class Solution {
public:
	vector<vector<int>> ShortestDistance(vector<vector<int>>&matrix){
	   // Code here
	   cout<<"1Jerin James";
	   int n = matrix.size();
	   vector<vector<int>> dist(n, vector<int>(n, INT_MAX));
       dist[0][0] = 0;
	   for(int i = 0; i < n; i++ ){
	       for(int j = 0; j < n; j++){
	           for(int k = 1; k <= matrix[i][j]; k++){
                   if(dist[i][j] == INT_MAX) break;
	               if(j+k < matrix.size())
	                    dist[i][j+k] = min(dist[i][j] + 1, dist[i][j+k]);
	               if(i+k < matrix.size())
	                    dist[i+k][j] = min(dist[i][j] + 1, dist[i+k][j]);
	           }
	       }
	   }
	   for(int i = 0; i < n; i++){
		   cout<<endl;
		   for(int j = 0; j < n; j++){
			   cout<< dist[i][j]<<" ";
		   }
	   }
	   cout<<"2Jerin James"<<endl;
	   vector<vector<int>> temp(1, vector<int>(1,-1));
	   
	   if(dist[n-1][n-1] >100 || dist[n-1][n-1] <=0) return temp;
	   vector<vector<int>> backtrack(n, vector<int>(n, 0));
	   backtrack[n-1][n-1]=1;
	   for(int i = n-1; i>=0; ){
	       for(int j = n-1; j>=0; ){
	           bool isDone = false;
               cout<<"Hi, we are here\n";
               cout<<"i = "<<i<<" , j = "<<j;
	           for(int k = 20; k > 0 ; k--){
                   cout<<k<<endl;
	               if(i-k>=0){
	                   if(dist[i-k][j] == dist[i][j]-1 && matrix[i-k][j] >=k){
                           cout<<"1st loop  =  "<<k<<endl;
    	                   i = i-k;
    	                   backtrack[i][j] = 1;
    	                   isDone = true;
    	                   break;
	                   }
	               }
	           }if(!isDone){
    	           for(int k = 20; k > 0 ; k--){
                       cout<<k<<endl;
    	               if(j-k>=0){
    	                   if(dist[i][j-k] == dist[i][j]-1 && matrix[i][j-k] >=k){
                               cout<<"2st loop  =  "<<k<<endl;
    	                   j = j-k;
    	                   backtrack[i][j] = 1;
                           isDone = true;
    	                   break;
    	                   }
    	               }
    	           }
	           }
            //    if(!isDone) return;
            if(i ==0 && j ==0){return backtrack;}
	       }
	   }
	   return backtrack;
	}

};

int main(){
    int tc;
    cin >>tc;
    while(tc--){
        int n;
        cout<<"Enter n";
        cin >> n;
        vector<vector<int>> matrix(n, vector<int>(n,0));
        for(int i = 0; i<n; i++){
            for(int j = 0; j<n; j++){
                cin >> matrix[i][j];
                cout<<" enter next";
            }
            cout<<"Finished";
        }
        cout<<"Finished";
        Solution obj;
        vector<vector<int>> ans = obj.ShortestDistance(matrix);
        for(auto i: ans){
            for(auto j: i){
                cout << j << " ";
            }
            cout<<"\n";
        }
    }
    return 0;
}
