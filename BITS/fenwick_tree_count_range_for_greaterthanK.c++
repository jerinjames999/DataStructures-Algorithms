//Time Complexity: O(N * log N) where N = (n+q)
#include <bits/stdc++.h>
using namespace std;

//I will sort the arr in desc order. and also the QueryK values also
// for each ele, there is a node with actual pos in arr and val = ele.
// loop on querySort, in it loop loop on nodearrsort, 
// for each ele, add 1 to the BIT tree at loc same as loc of ele.pos
// for query find sum from L to R
// at last print the Q results in order
// reason this works is that we sorted so we will only consider the greatest ele first, and for supporting range query 
// we are maintaining  a BIT tree to find sum in the range.

// This only works for offline queries.

class node{
	public:
	int ele;
	int pos;
	bool operator<(node &a){
		return ele > a.ele;
	}
};
class Qnode{
	public:
	int k;
	int pos;
	bool operator<(Qnode &a){
		return k > a.k;
	}
};

class BITS
{
    int n;
    vector<int> bits;
    public:
    BITS(vector<node> &arr){
        n = arr.size();
        bits.resize(n+1, 0);
        //preprocess(arr);
    }
    // void preprocess(vector<node>& arr){
    //     for(int i = 0; i<n; i++){
    //         update(i, arr[i]);
    //     }
    // }
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
    vector<int> arr = { 7, 3, 9, 13, 5, 4 };
    //{2, 5, 3, 6, 1 , 9, 1, 3, 10, -1};
    // for(int i = 0; i<n; i++){
    //     cin>>arr[i];
    // }
	vector<node> node_arr(n+1);
	for(int i = 0; i< n; i++){
		node_arr[i].ele = arr[i];
		node_arr[i].pos = i;
	}
    node_arr[n].ele = INT_MIN;
    node_arr[n].pos = n;
	sort(node_arr.begin(), node_arr.end());
    int q;
    cin>>q;
	vector<vector<int>> Query(q, vector<int>(3));

	vector<Qnode> Qnode_arr(q);
	vector<int> Qans(q);

	for(int i = 0; i<q; i++){
        cin>>Query[i][0]>>Query[i][1]>>Query[i][2];
        Query[i][0]--;Query[i][1]--;
		Qnode_arr[i].k = Query[i][2];
		Qnode_arr[i].pos = i;
    }
	sort(Qnode_arr.begin(), Qnode_arr.end());

	BITS bitTree(node_arr);
	int j = 0, i = 0;
	while(1){
		for(; j<n &&node_arr[j].ele> Qnode_arr[i].k ; j++){
			bitTree.update( node_arr[j].pos, 1);
		}
		for(; i<q && Qnode_arr[i].k>=node_arr[j].ele; i++){
            Qans[Qnode_arr[i].pos] = bitTree.sum( Query[Qnode_arr[i].pos][0], Query[Qnode_arr[i].pos][1] );
        }
        // cout<<"\n"<<i<<" "<<j;
        if(i==q)break;
	}
    cout<<"\n";
    for(int a = 0; a<q; a++){
        cout<<Qans[a]<<"  ";
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
