// Adding numbers using fenwick Tree
#include <bits/stdc++.h>
using namespace std;

class BITS
{
    int n;
    vector<int> bits;
    public:
    BITS(int size){
        n = size;
        bits.resize(n+1, 0);
    }
    BITS(vector<int> &arr){
        n = arr.size();
        bits.resize(n+1, 0);
        preprocess(arr);
    }
    void preprocess(vector<int>& arr){
        for(int i = 0; i<n; i++){
            update(i, arr[i]);
        }
    }
    void update(int idx, int diff){
        idx++;
        for(int i = idx; i<n+1; i += i&(-i)){
            bits[i]+= diff;
        }
    }
    int query(int r){
        int sum = 0;
        for(int i = r; i!=0; i -= i&(-i)){
            sum += bits[i];
        }
        return sum;
    }
    int sum(int l, int r){
        return query(r+1)-query(l);
    }

};

void solve()
{
    int n;
    n = 10;
    vector<int> arr(n);
    for(int i = 0; i<n; i++){
        cin>>arr[i];
    }
    BITS SUM(arr);
    int q;
    cin>>q;
    while(q--){
        int l, r;
        cin>>l>>r;
        cout<<SUM.sum(l, r);
        int idx, val;
        cin>>idx>>val;
        SUM.update(idx, val - arr[idx]);
    }
}

int main()
{

    int T;
    T = 1;
    while (T--)
    {
        solve();
    }
    return 0;
}