#include <bits/stdc++.h>
using namespace std;

class LCA
{
    int N, root, LOG;
    vector<vector<int>> up;
    vector<int> parent;
    vector<int> height;

public:
    LCA(vector<vector<int>> arr, int root)
    {
        this->root = root;
        this->N = arr.size();
        LOG = int(log2(N))+1;
        up.resize(N, vector<int>(LOG));
        parent.resize(N);
        parent[root] = root;
		height.resize(N, 0);
        preprocess(arr);
    }
    
    void preprocess(vector<vector<int>> arr)
    {
        dfs_parent(arr, root, -1);
        dfs_height(arr, root, -1);
        for (int i = 0; i < N; i++)
        {
            up[i][0] = parent[i];
        }
        for (int i = 1; i < int(LOG); i++)
        {
            for (int j = 0; j < N; j++)
            {
                up[j][i] = up[up[j][i - 1]][i - 1];
            }
        }
    }
    void dfs_parent(vector<vector<int>> arr, int rt, int prt)
    {
        for (int i = 0; i < arr[rt].size(); i++)
        {
            if (arr[rt][i] == prt)
                continue;
            parent[arr[rt][i]] = rt;
            dfs_parent(arr, arr[rt][i], rt);
        }
    }
	void dfs_height(vector<vector<int>> arr, int rt, int prt)
    {	

        for (int i = 0; i < arr[rt].size(); i++)
        {
            if (arr[rt][i] == prt)
                continue;
			
            height[arr[rt][i]] = height[rt]+1;
            dfs_height(arr, arr[rt][i], rt);
        }
    }
    int kth_ancestor(int node, int k)
    {
        if (k == 0)
            return node;
        int curr = node;
        for (int i = 0; i < LOG; i++)
        {
            if (k < (1 << i))
                break;
            if (k & (1 << i))
            {
                curr = up[curr][i];
            }
        }
        return curr;
    }
	int lca(int n1, int n2){
        
		if(height[n2]>height[n1]){
			return lca(n2, n1);  
		}
		n1 = kth_ancestor(n1, height[n1] - height[n2]);
		if(n1==n2)return n1;
		for(int i = LOG-1; i>=0; i--){
			if(up[n1][i]!=up[n2][i]){
				n1 = up[n1][i], n2 = up[n2][i];
			}
		}
		return up[n1][0];
	}
};

void solve()
{
    int N;
    cin >> N;
    vector<vector<int>> tree(N, vector<int>());
    for (int i = 0; i < N - 1; i++)
    {
        int a, b;
        cin >> a >> b;
        a--;
        b--;
        tree[a].push_back(b);
        tree[b].push_back(a);
    }
    LCA T(tree, 0);

    int node1, node2;
    int q;
    cin >> q;

    while (q--)
    {
        cin >> node1 >> node2;
        node1--, node2--;
        cout << T.lca(node1, node2) << endl;
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