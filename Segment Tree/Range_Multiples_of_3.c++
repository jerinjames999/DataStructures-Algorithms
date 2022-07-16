#include<bits/stdc++.h>
using namespace std;

class SegTree{
    int SegSize, n;
    vector<vector<int>> *SegVec;
    vector<int> *LazyTree;
    public:
    SegTree(vector<int>& arr){
        n = arr.size();
        int power = (int)log2(n);
        if(log2(n) == power) power++;
        else
            power += 2;
        SegSize = 1<<power;
        SegVec = new vector<vector<int>>(SegSize, vector<int>(3, 0));
        LazyTree = new vector<int>(SegSize, 0);
        BuildTree(0, 0, n-1, arr);
        cout << endl;
        for (int i = 0; i < SegSize; i++)
        {
            //cout << i << " - " << (*SegVec)[i] << endl;
        }
    }
    void BuildTree(int si, int ss, int se,vector<int>& arr){
        cout << "{" << si << " " << ss << " " << se << "}" << endl;
        if(ss==se){
            (*SegVec)[si][arr[ss]%3] = 1;
            return ;
        }
        int mid = ss + (se-ss)/2;
        BuildTree(2*si+1, ss, mid, arr);
        BuildTree(2*si+2, mid+1, se, arr);
        (*SegVec)[si] = Merge(2*si+1, 2*si+2);
    }
    vector<int> Merge(int l, int r){
        vector<int> modRes(3);
        for(int i = 0; i<3; i++){
            modRes[i] = (*SegVec)[l][i] + (*SegVec)[r][i];
        }
        return modRes;
    }
    int MergeResult(int l, int r){
        return l + r;
    }
    vector<int> RightShift(vector<int> modvec, int dx){
        std::rotate(modvec.begin(), modvec.begin()+modvec.size()-dx, modvec.end());
        return modvec;
    }
    int RangeQuery(int si, int ss, int se, int qs, int qe){

        if((*LazyTree)[si] != 0){
            int dx = (*LazyTree)[si];
            (*LazyTree)[si] = 0;
            (*SegVec)[si] = RightShift((*SegVec)[si], dx);
            if(ss!=se){
                (*LazyTree)[2*si+1] = ((*LazyTree)[2*si+1] + dx)%3;
                (*LazyTree)[2*si+2] = ((*LazyTree)[2*si+2] + dx)%3;
            }
        }

        if(qs>se || qe<ss)return 0;
        if(qs<=ss && qe>=se)return (*SegVec)[si][0];
        int mid = ss+(se-ss)/2;
        int l = RangeQuery(2*si+1, ss, mid, qs, qe);
        int r = RangeQuery(2*si+2, mid+1, se, qs, qe);
        return MergeResult(l,r);
    }
    void RangeUpdate(int si, int ss, int se, int qs, int qe, int val){
        if((*LazyTree)[si] != 0){
            cout<<"continuing0..."<<endl;
            int dx = (*LazyTree)[si];
            (*LazyTree)[si] = 0;
            (*SegVec)[si] = RightShift((*SegVec)[si], dx);
            if(ss!=se){
                (*LazyTree)[2*si+1] = ((*LazyTree)[2*si+1] + dx)%3;
                (*LazyTree)[2*si+2] = ((*LazyTree)[2*si+2] + dx)%3;
            }
        }
        cout<<"continuing..."<<endl;
        if(qs>se || qe<ss) return;
        if(qs<=ss && qe>=se){
            int dx = val;
            (*SegVec)[si] = RightShift((*SegVec)[si], dx);
            if(ss != se){
                (*LazyTree)[2*si+1] = ((*LazyTree)[2*si+1] + dx)%3;
                (*LazyTree)[2*si+2] = ((*LazyTree)[2*si+2] + dx)%3;
            }
            return;
        }
        int mid = ss + (se -ss)/2;
        RangeUpdate(2*si+1, ss, mid, qs, qe, val);
        RangeUpdate(2*si+2, mid+1, se, qs, qe, val);
        (*SegVec)[si] = Merge(2*si+1, 2*si + 2);
        if(ss == 0 && se == n-1){
            for (int i = 0; i < (*LazyTree).size(); i++)
            {
                cout << i << " - " << (*LazyTree)[i] << endl;
            }
        }
    }
    ~SegTree()
    {
        delete[] SegVec;
        delete[] LazyTree;
    }
};

int main(){

    int n;
    cin >> n;
    vector<int> arr(n);
    for (int i = 0; i < n; i++)
    {
        cin >> arr[i];
    }
    SegTree Seg(arr);
    int qn;
    cout << "No of Queries : ";
    cin >> qn;
    vector<vector<int>> Query(qn, vector<int>(3));
    for (int i = 0; i < qn; i++)
    {
        cin >> Query[i][0] >> Query[i][1] >> Query[i][2]; //1 for update 2 for query;
    }
    for (int i = 0; i < qn; i++)
    {
        if (Query[i][0] == 0)
        {
            for(int j = 0; j< Query[i][2]- Query[i][1] + 1; j++){
                arr[Query[i][1]+j]++;
                cout<<j<<endl;
            }
            cout<<"Started"<<endl;
            Seg.RangeUpdate(0, 0, n-1, Query[i][1], Query[i][2], 1);
            cout<<"finished"<<endl;
        }
        else if(Query[i][0] == 1){
            cout << "RangeQuery(" << Query[i][1] << ", " << Query[i][2] << ")   :   " << Seg.RangeQuery(0, 0, n - 1, Query[i][1], Query[i][2]) << endl;
        }
    }
    return 0;
}


//ios_base::sync_with_stdio(false);
// cin.tie(0);
// cout.tie(0);