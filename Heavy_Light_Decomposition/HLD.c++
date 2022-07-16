// HLD for adding vertex weights along the path between n1 and n2 using segTree for addition. supports vertex weight updation.
#include <bits/stdc++.h>
using namespace std;

class SegTree
{
    int SegSize, n;
    vector<int> *SegVec, *LazyTree;

public:
    SegTree(vector<int> &arr)
    {
        n = arr.size();
        int power = (int)log2(n);
        if (log2(n) == power)
            power++;
        else
            power += 2;
        SegSize = 1 << power;
        SegVec = new vector<int>(SegSize);
        LazyTree = new vector<int>(SegSize, 0);
        BuildTree(0, 0, n - 1, arr);
        cout << endl;
        for (int i = 0; i < SegSize; i++)
        {
            cout << i << " - " << (*SegVec)[i] << endl;
        }
    }
    void BuildTree(int si, int ss, int se, vector<int> &arr)
    {
        cout << "{" << si << " " << ss << " " << se << "}" << endl;
        if (ss == se)
        {
            (*SegVec)[si] = arr[ss];
            return;
        }
        int mid = ss + (se - ss) / 2;
        BuildTree(2 * si + 1, ss, mid, arr);
        BuildTree(2 * si + 2, mid + 1, se, arr);
        (*SegVec)[si] = Merge(2 * si + 1, 2 * si + 2);
    }
    int Merge(int l, int r)
    {
        return (*SegVec)[l] + (*SegVec)[r];
    }
    int MergeResult(int l, int r)
    {
        return l + r;
    }
    int RangeQuery(int si, int ss, int se, int qs, int qe)
    {

        if ((*LazyTree)[si] != 0)
        {
            int dx = (*LazyTree)[si];
            (*LazyTree)[si] = 0;
            (*SegVec)[si] += (se - ss + 1) * dx;
            if (ss != se)
            {
                (*LazyTree)[2 * si + 1] += dx;
                (*LazyTree)[2 * si + 2] += dx;
            }
        }

        if (qs > se || qe < ss)
            return 0;
        if (qs <= ss && qe >= se)
            return (*SegVec)[si];
        int mid = ss + (se - ss) / 2;
        int l = RangeQuery(2 * si + 1, ss, mid, qs, qe);
        int r = RangeQuery(2 * si + 2, mid + 1, se, qs, qe);
        return MergeResult(l, r);
    }
    void Update(int si, int ss, int se, int idx, int val)
    {
        if ((*LazyTree)[si] != 0)
        {
            int dx = (*LazyTree)[si];
            (*LazyTree)[si] = 0;
            (*SegVec)[si] += (se - ss + 1) * dx;
            if (ss != se)
            {
                (*LazyTree)[2 * si + 1] += dx;
                (*LazyTree)[2 * si + 2] += dx;
            }
        }
        if (ss == se)
        {
            (*SegVec)[si] += val;
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
        if (ss == 0 && se == n - 1)
        {
            for (int i = 0; i < SegSize; i++)
            {
                cout << i << " - " << (*SegVec)[i] << endl;
            }
        }
    }
    void RangeUpdate(int si, int ss, int se, int qs, int qe, int val)
    {
        if ((*LazyTree)[si] != 0)
        {
            int dx = (*LazyTree)[si];
            (*LazyTree)[si] = 0;
            (*SegVec)[si] += (se - ss + 1) * dx;
            if (ss != se)
            {
                (*LazyTree)[2 * si + 1] += dx;
                (*LazyTree)[2 * si + 2] += dx;
            }
        }
        if (qs > se || qe < ss)
            return;
        if (qs <= ss && qe >= se)
        {
            int dx = (se - ss + 1) * val;
            (*SegVec)[si] += dx;
            if (ss != se)
            {
                (*LazyTree)[2 * si + 1] += val;
                (*LazyTree)[2 * si + 2] += val;
            }
            return;
        }
        int mid = ss + (se - ss) / 2;
        RangeUpdate(2 * si + 1, ss, mid, qs, qe, val);
        RangeUpdate(2 * si + 2, mid + 1, se, qs, qe, val);
        (*SegVec)[si] = Merge(2 * si + 1, 2 * si + 2);
    }
    ~SegTree()
    {
        cout << "deleting everything" << endl;
        delete[] LazyTree;
        delete[] SegVec;
    }
};

class HLD
{
    int N, root, LOG;
    vector<vector<int>> up;
    vector<int> parent; // done
    vector<int> heavy;  // done
    vector<int> depth;  // done
    vector<int> height; // done
    vector<int> sz;     // done

    int chainID = 0, pos = 0;
    vector<int> sg_node_pos; // position of node in segTree
    vector<int> chain;       // chainid of each node
    vector<int> chainHead;   // node which is the head of the chain
    vector<int> sg_arr;
    vector<int> v_weight;
    SegTree *Seg;

public:
    HLD(vector<vector<int>> tree, int root, vector<int> vertix_weight)
    {
        cout << "HLD init...\n";
        this->root = root;
        this->N = tree.size();
        LOG = int(log2(N)) + 1;
        up.resize(N, vector<int>(LOG));
        v_weight = vertix_weight;
        parent.resize(N);
        parent[root] = root;
        depth.resize(N, 0);
        height.resize(N, 0);
        sz.resize(N, 0);
        heavy.resize(N, 0);
        chain.resize(N);
        chainHead.resize(N);
        sg_node_pos.resize(N);
        sg_arr.resize(N);

        preprocess(tree);
        decompose(root, -1, tree);
        cout << "segTree init...\n";
        Seg = new SegTree(sg_arr);
        cout << "segTree exit...\n";
        cout << "HLD exit...\n";
    }
    void preprocess(vector<vector<int>> arr)
    {
        cout << "preprocess init...\n";
        dfs(arr, root, -1);
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
        cout << "preprocess exit...\n";
    }
    void decompose(int rt, int prt, vector<vector<int>> tree)
    {
        cout << "decompose init...\n";
        chain[rt] = chainID;
        sg_node_pos[rt] = pos;
        sg_arr[pos] = v_weight[rt]; // edge or vertix value, now it's vertix index;
        pos++;
        if (heavy[rt] != -1)
        {
            decompose(heavy[rt], rt, tree);
        }
        for (int i = 0; i < tree[rt].size(); i++)
        {
            if (tree[rt][i] != prt && tree[rt][i] != heavy[rt])
            {
                chainID++;
                chainHead[chainID] = tree[rt][i];
                decompose(tree[rt][i], rt, tree);
            }
        }

        cout << "decompose exit...\n";
    }
    int sum_query(int n1, int n2)
    {
        int x = lca(n1, n2);
        cout << "x = " << x << endl;
        int sum = 0;
        while (chain[x] != chain[n1])
        {
            sum += Seg->RangeQuery(0, 0, N - 1, sg_node_pos[chainHead[chain[n1]]], sg_node_pos[n1]);
            n1 = parent[chainHead[chain[n1]]];
        }
        sum += Seg->RangeQuery(0, 0, N - 1, sg_node_pos[x], sg_node_pos[n1]);
        while (chain[x] != chain[n2])
        {
            sum += Seg->RangeQuery(0, 0, N - 1, sg_node_pos[chainHead[chain[n2]]], sg_node_pos[n2]);
            n2 = parent[chainHead[chain[n2]]];
        }
        // sum += Seg->RangeQuery(0, 0, N-1, sg_node_pos[x], sg_node_pos[n2]);
        // sum -= v_weight[x];//no corresponding value, substracted index of vertix;
        return sum;
    }
    int update_query(int n, int diff)
    {
        v_weight[n] = diff;
        Seg->Update(0, 0, N - 1, sg_node_pos[n], diff);
    }
    void dfs(vector<vector<int>> arr, int rt, int prt)
    { // done
        cout << "dfs init...\n";
        sz[rt] = 1;
        for (int i = 0; i < arr[rt].size(); i++)
        {
            if (arr[rt][i] == prt)
                continue;
            parent[arr[rt][i]] = rt;
            height[arr[rt][i]] = height[rt] + 1;
            dfs(arr, arr[rt][i], rt);
        }
        int max_depth = -1, hv_node = -1;
        for (int i = 0; i < arr[rt].size(); i++)
        {
            if (arr[rt][i] == prt)
                continue;
            sz[rt] += sz[arr[rt][i]];
            if (max_depth < depth[arr[rt][i]])
            {
                max_depth = depth[arr[rt][i]];
                hv_node = arr[rt][i];
            }
        }
        depth[rt] = max_depth + 1;
        heavy[rt] = hv_node;
        cout << "dfs exit...\n";
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
    int lca(int n1, int n2)
    {

        if (height[n2] > height[n1])
        {
            return lca(n2, n1);
        }
        n1 = kth_ancestor(n1, height[n1] - height[n2]);
        if (n1 == n2)
            return n1;
        for (int i = LOG - 1; i >= 0; i--)
        {
            if (up[n1][i] != up[n2][i])
            {
                n1 = up[n1][i], n2 = up[n2][i];
            }
        }
        return up[n1][0];
    }
    ~HLD()
    {
        delete Seg;
    }
};
/*
12
1 2
2 4
4 6
6 10
4 9
2 7
7 8
1 3
3 5
5 11
5 12
1 2 3 4 5 6 7 8 9 10 11 12
*/
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
    vector<int> vertix_weight(N);
    for (int i = 0; i < N; i++)
    {
        cin >> vertix_weight[i];
    }

    HLD hld(tree, 0, vertix_weight);

    int q;
    cin >> q;
    int node1, node2, qtype, diff;

    while (q--)
    {
        cin >> qtype;
        if (qtype == 1)
        {
            cin >> node1 >> node2;
            node1--, node2--;
            cout << hld.sum_query(node1, node2) << endl;
        }
        else
        {
            cin >> node1 >> diff;
            node1--;
            hld.update_query(node1, diff);
        }
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