#include<bits/stdc++.h>
using namespace std;

vector<int> solve (int N, vector<string> S, int Q, vector<vector<int> > query) {
   // Write your code here

   vector<int> ans;
   int MaxN = 1e5;

   vector<vector<int>> seg(4*MaxN, vector<int>(26, 0));

   vector<int> merge(int l, int r){
      vector<int> res(26, 0);
      for(int i = 0; i<26; i++){
         res[i] = seg[l][i]+seg[r][i];
         res[i] = res[i]%2;
      }
      return res;
   }
   vector<int> MergeRs(vector<int> l, vector<int> r){
       vector<int> res(26, 0);
       for(int i = 0; i<26; i++){
           res[i] = l[i]+r[i];
           res[i] = res[i]%2;
       }
       return res;
   }
   void build(int si, int ss, int se, vector<string> S){
      if(ss == se){
         for(int i = 0 ; i<S[ss]; i++){
            seg[si][S[ss][i]-'a'] = 1;
            return;
         }
         int mid = ss + (se-ss)/2;
         build(2*si+1, ss, mid, S);
         build(2*si+1, mid+1, se, S);
         seg[si] = merge(2*si+1, 2*si+2);
      }
   }

   void Update(int si, int ss, int se, int idx, int val){
      if(ss== se){
          seg[si][val] = (seg[si][val]+1)%2;
      }else{
         int mid = ss + (se-ss)/2;
         if(ss<= idx && idx<= mid){
            Update(2*si+1, ss, mid, idx);
         }else{
            Update(2*si+2, mid+1, se, idx);
         }
         seg[si] = merge(2*si+1, 2*si+2);
      }
   }
   vector<int> RangeQuery(int si, int ss, int se, int qs, int qe){
      if(qs>se||qe<ss)return vector<int>(26, 0);
      if(qs<=se&&qe>=ss)return seg[si];
      
      int mid = ss + (se-ss)/2;
      vector<int> l = RangeQuery(2*si+1, ss, mid, qs, qe);
      vector<int> r = RangeQuery(2*si+2, mid+1, se, qs, qe);
      return MergeRs(l,r);
    }


    
    int q = 0;
    while(Q--){
        if(query[q][0]==1)
            ans.push_back(RangeQuery(0, 0, n - 1, Query[i][1], Query[i][2]));
    }

   
}

int main() {

    ios::sync_with_stdio(0);
    cin.tie(0);
    int N;
    cin >> N;
    vector<string> S(N);
    for(int i_S = 0; i_S < N; i_S++)
    {
    	cin >> S[i_S];
    }
    int Q;
    cin >> Q;
    vector<vector<int> > query(Q, vector<int>(3));
    for (int i_query = 0; i_query < Q; i_query++)
    {
    	for(int j_query = 0; j_query < 3; j_query++)
    	{
    		cin >> query[i_query][j_query];
    	}
    }

    vector<int> out_;
    out_ = solve(N, S, Q, query);
    cout << out_[0];
    for(int i_out_ = 1; i_out_ < out_.size(); i_out_++)
    {
    	cout << " " << out_[i_out_];
    }
}