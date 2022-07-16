#include<bits/stdc++.h>
using namespace std;

class Solution {
public:
	vector<vector<int>> ShortestDistance(vector<vector<int>>&matrix){
	   // Code here
	   cout<<"1Jerin James";
	   int n = matrix.size();
	   vector<vector<int>> dist(n, vector<int>(n, INT_MAX));
	   for(int i = 0; i < n; i++ ){
	       for(int j = 0; j < n; j++){
	           for(int k = 1; k <= matrix[i][j]; k++){
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
	   cout<<"2Jerin James";
	   vector<vector<int>> backtrack(n, vector<int>(n, 0));
	   //if(dist[n-1][n-1] == INT_MAX) return -1;
	   backtrack[n-1][n-1]=1;
	   for(int i = n-1; i>=0; ){
	       for(int j = n-1; j>=0; ){
	           bool isDone = false;
	           for(int k = 20; k > 0 ; k--){
	               if(i-k>=0){
	                   if(dist[i-k][j] == dist[i][j]-1 && matrix[i-k][j] >=k){
    	                   i = i-k;
    	                   backtrack[i][j] = 1;
    	                   isDone = true;
    	                   break;
	                   }
	               }
	           }if(!isDone){
    	           for(int k = 20; k > 0 ; k--){
    	               if(j-k>=0){
    	                   if(dist[i][j-k] == dist[i][j]-1 && matrix[i][j-k] >=k){
    	                   j = j-k;
    	                   backtrack[i][j] = 1;
    	                   break;
    	                   }
    	               }
    	           }
	           }
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
