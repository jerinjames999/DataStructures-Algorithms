#include<bits/stdc++.h>
using namespace std;

class SegmentTree{
    int n, k;
    vector<vector<int>> SegArray;
    public:
    SegmentTree(int n, int k): n(n), k(k){
        SegArray = vector<vector<int>>(4*n, vector<int>(k, 0));
    }

    vector<int> RangeSum(int si, int ss,int se, int qs, int qe){
        if(ss>=qs && se<=qe){
            return SegArray[si];
        }
        if(qe<ss || qs>se){
            return vector<int>(k,0);
        }
        int mid = (ss+se)/2;
        vector<int> a = RangeSum(2*si+1, ss, mid, qs, qe);
        vector<int> b = RangeSum(2*si+2, mid+1, se, qs, qe);
        vector<int> sm(k);
        for(int i = 0; i<k;i++){
            sm[i] = a[i]+b[i];
        }
        return sm;
    }

    void update(int si, int ss,int se, int pos, vector<int> val){
        cout<<"*"<<si<<" "<<ss<<" "<<se<<" "<<pos<<endl;
        if(ss==se){
            SegArray[si] = val;
            return;
        }
        int mid = (ss+se)/2;
        if(ss<=pos && pos<=mid){
            update(2*si+1, ss, mid, pos,val);
        }else{
            update(2*si+2, mid+1,se, pos, val);
        }
        for(int i = 0; i<k;i++){
            SegArray[si][i] = SegArray[2*si+1][i]+SegArray[2*si+2][i];
        }
    }

};


int main(){
    int n, k;
    cin>>n>>k;
    vector<int> arr(n);
    for(int i = 0; i<n; i++){
        cin>>arr[i];
    }
    SegmentTree st(n,k);
    vector<int> sum(k);
    cout<<"Hi1"<<endl;
    for(int i = 0; i<n; i++){
    cout<<"Hi2"<<endl;
        vector<int> temp = st.RangeSum(0, 0, n-1, 0, arr[i]-1);
    cout<<"Hi"<<endl;
        sum[0] = 1;
        for(int j = 0;j<k-1; j++){
            sum[j+1] = temp[j];
        }
        st.update(0, 0, n-1, arr[i]-1, sum);
    cout<<"Hi"<<endl;
    }
    cout<<st.RangeSum(0, 0, n-1, 0, n-1)[k-1]<<"\n";

    return 0;
}