//A Maze is given as n*n matrix of blocks where source block is the upper left most block i.e., matrix[0][0] and destination block is lower rightmost block i.e., matrix[n-1][n-1]. A rat starts from source and has to reach the destination. The rat can move in only two directions: first forward if possible or down. If multiple solutions exist, the 
//Shortest earliest hop will be accepted. For the same hop distance at any point, forward will be preferred over downward. In the maze matrix, 0 means the block is the dead end and non-zero number means the block can be used in the path from source to destination. The non-zero value of mat[i][j] indicates number of maximum jumps rat can make from cell mat[i][j]. In this variation, Rat is allowed to jump multiple steps at a time instead of 1. Find a matrix which describes the position the rat to reach at the destination.
 

#include<bits/stdc++.h>
using namespace std;

int PossibleToReachOrigin(vector<vector<int>> &matrix, vector<vector<int>> &backtrack, int i, int j){
    if(backtrack[i][j]==1){
        return 1;
    }

    for(int k = 1; k <21; k++){
        //boundary condition;
        if(i-k>-1){
            if(matrix[i-k][j] >=k && backtrack[i-k][j]!=0){
                
                backtrack[i-k][j] =PossibleToReachOrigin(matrix, backtrack, i-k, j );
                if(backtrack[i-k][j]==1){
                    return 1;
                }
            }
        }
        else{
            break;
        }
    }
    for(int k = 1; k <21; k++){
        //boundary condition;
        if(j-k>-1){
            if(matrix[i][j-k] >=k && backtrack[i][j-k]!=0){
                backtrack[i][j-k] =PossibleToReachOrigin(matrix, backtrack, i, j-k );
                if(backtrack[i][j-k]){
                    return 1;
                }
            }
        }
        else{
            break;
        }
    }
    return 0;
}

class Solution {
public:
	vector<vector<int>> ShortestDistance(vector<vector<int>>&matrix){
	   // Code here
	    int n = matrix.size();
        vector<vector<int>> backtrack(n, vector<int>(n, -1));
        backtrack[0][0] = 1;
        backtrack[n-1][n-1] = PossibleToReachOrigin(matrix, backtrack, n-1, n-1);
        vector<vector<int>> temp(1, vector<int>(1,-1));
        for(auto &vec : backtrack)
            for(auto &el : vec){
                if(el == -1){
                    el = 0;
                }
            }
        if(backtrack[n-1][n-1])
            return backtrack;
        else
            return temp;

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
