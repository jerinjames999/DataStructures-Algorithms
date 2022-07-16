#include<bits/stdc++.h>
using namespace std;

class SegTree{
    int SegSize, n;
    vector<int> *SegVec;
    public:
    SegTree(vector<int>& arr){
        n = arr.size();
        int power = (int)log2(n);
        if(log2(n) == power) power++;
        else
            power += 2;
        SegSize = 1<<power;
        SegVec = new vector<int>(SegSize);
        BuildTree(0, 0, n-1, arr);
        cout << endl;
        for (int i = 0; i < SegSize; i++)
        {
            cout << i << " - " << (*SegVec)[i] << endl;
        }
    }
    void BuildTree(int si, int ss, int se,vector<int>& arr){
        cout << "{" << si << " " << ss << " " << se << "}" << endl;
        if(ss==se){
            (*SegVec)[si] = !(arr[ss]&1);
            return ;
        }
        int mid = ss + (se-ss)/2;
        BuildTree(2*si+1, ss, mid, arr);
        BuildTree(2*si+2, mid+1, se, arr);
        (*SegVec)[si] = Merge(2*si+1, 2*si+2);
    }
    int Merge(int l, int r){
        return (*SegVec)[l] + (*SegVec)[r];
    }
    int MergeResult(int l, int r){
        return l + r;
    }
    int RangeQuery(int si, int ss, int se, int qs, int qe){
        if(qs>se || qe<ss)return 0;
        if(qs<=ss && qe>=se)return (*SegVec)[si];
        int mid = ss+(se-ss)/2;
        int l = RangeQuery(2*si+1, ss, mid, qs, qe);
        int r = RangeQuery(2*si+2, mid+1, se, qs, qe);
        return MergeResult(l,r);
    }
    void Update(int si, int ss, int se, int idx, int val)
    {
        if (ss == se)
        {
            (*SegVec)[si] = !(val&1);
        }
        else
        {
            int mid = ss + (se - ss) / 2;
            if (ss <= idx && idx <= mid)
            {
                Update(2 * si + 1, ss, mid, idx, val);
            }
            else
            {
                Update(2 * si + 2, mid + 1, se, idx, val);
            }
            (*SegVec)[si] = Merge(2 * si + 1, 2 * si + 2);
        }
        if(ss == 0 && se == n-1){
            for (int i = 0; i < SegSize; i++)
            {
                cout << i << " - " << (*SegVec)[i] << endl;
            }
        }
        
    }
    ~SegTree()
    {
        delete[] SegVec;
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
        if (Query[i][0] == 1)
        {
            arr[Query[i][1]] = Query[i][2];
            Seg.Update(0, 0, n - 1, Query[i][1], Query[i][2]);
        }
        else if (Query[i][0] == 2)
        {
            cout << "RangeQuery(" << Query[i][1] << ", " << Query[i][2] << " - Even)   :   " << Seg.RangeQuery(0, 0, n - 1, Query[i][1], Query[i][2]) << endl;
        }
        else if (Query[i][0] ==3){
            cout << "RangeQuery(" << Query[i][1] << ", " << Query[i][2] << " - Odd)   :   " << Query[i][2]-Query[i][1] + 1 - Seg.RangeQuery(0, 0, n - 1, Query[i][1], Query[i][2]) << endl;
        }
    }
    return 0;
}