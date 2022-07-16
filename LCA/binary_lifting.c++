#include <bits/stdc++.h>
using namespace std;

class TreeAncestor
{
    int N, root, LOG;
    vector<vector<int>> up;
    vector<int> parent;

public:
    TreeAncestor(vector<vector<int>> arr, int root)
    {
        this->root = root;
        this->N = arr.size();
        LOG = int(log2(N))+1;
        up.resize(N, vector<int>(LOG));
        parent.resize(N);
        parent[root] = root;
        preprocess(arr);
    }
    void preprocess(vector<vector<int>> arr)
    {
        dfs_parent(arr, root, -1);
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
    TreeAncestor T(tree, 0);

    int node, k;
    int q;
    cin >> q;

    while (q--)
    {
        cin >> node >> k;
        node--;
        cout << T.kth_ancestor(node, k) << endl;
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