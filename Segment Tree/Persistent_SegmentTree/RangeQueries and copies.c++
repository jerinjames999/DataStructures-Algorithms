#include <iostream>
#include <algorithm>
#include <vector>
#include <map>
#include <set>
#include <array>
#include <stack>
#include <queue>
#include <random>
#include <numeric>
#include <functional>
#include <chrono>
#include <utility>
#include <iomanip>
#include <assert.h>

using namespace std;

void dbg_out() { cerr << endl; }
template <typename Head, typename... Tail>
void dbg_out(Head H, Tail... T)
{
    cerr << ' ' << H;
    dbg_out(T...);
}
#define dbg(...) cerr << "(" << #__VA_ARGS__ << "):", dbg_out(__VA_ARGS__)

#define rng_init mt19937 rng(chrono::steady_clock::now().time_since_epoch().count())
#define rng_seed(x) mt19937 rng(x)
#define all(x) (x).begin(), (x).end()
#define sz(x) (int)(x).size()
#define int long long

const int MXN = 4e5 + 5, INF = 1e9 + 5, MXK = 22;
int N, Q;
int A[MXN];
pair<int, int> child[MXN * MXK];
int tree[MXN * MXK], root[MXN];
int ptr, list_size;

void modify(int cur, int prev, int l, int r, int pos, int val)
{
    if (l == r)
    {
        tree[cur] = val;
        return;
    }

    int mid = (l + r) / 2;
    if (pos <= mid)
    {
        child[cur].first = ++ptr;
        child[cur].second = child[prev].second;

        modify(child[cur].first, child[prev].first, l, mid, pos, val);
    }
    else
    {
        child[cur].first = child[prev].first;
        child[cur].second = ++ptr;

        modify(child[cur].second, child[prev].second, mid + 1, r, pos, val);
    }

    tree[cur] = tree[child[cur].first] + tree[child[cur].second];
}

void modify(int new_version, int prev_version, int pos, int val)
{
    modify(new_version, prev_version, 0, N - 1, pos, val);
}

int query(int node, int l, int r, int ql, int qr)
{
    if (node == 0)
        return 0;
    if (l > qr || r < ql)
        return 0;
    if (l >= ql && r <= qr)
        return tree[node];

    int mid = (l + r) / 2;
    return query(child[node].first, l, mid, ql, qr) + query(child[node].second, mid + 1, r, ql, qr);
}

int query(int version, int l, int r)
{
    return query(version, 0, N - 1, l, r);
}

void solve()
{
    cin >> N >> Q;

    for (int i = 0; i < N; i++)
    {
        cin >> A[i];

        int prev_root = root[1];
        root[1] = ++ptr;
        modify(root[1], prev_root, i, A[i]);
    }

    list_size = 1;

    while (Q--)
    {
        int type;
        cin >> type;

        if (type == 1)
        {
            int a, k, x;
            cin >> k >> a >> x;
            a--;

            int new_root = ++ptr;
            modify(new_root, root[k], a, x);

            root[k] = new_root;
        }
        else if (type == 2)
        {
            int k, l, r;
            cin >> k >> l >> r;
            l--, r--;

            cout << query(root[k], l, r) << "\n";
        }
        else
        {
            int k;
            cin >> k;

            root[++list_size] = root[k];
        }
    }
}

signed main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int TC = 1;
    // cin >> TC;
    while (TC--)
        solve();
}