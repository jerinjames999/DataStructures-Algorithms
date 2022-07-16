#include <bits/stdc++.h>
using namespace std;

class Node
{
public:
    int sum = 0;
    Node *left = NULL;
    Node *right = NULL;
    Node(int data)
    {
        sum = data;
    }
    Node(Node *l, Node *r)
    {
        sum = (*l).sum + (*r).sum;
        left = l;
        right = r;
    }
};

Node *build(int start, int end)
{
    if (start == end)
    {
        return new Node(0);
    }
    else
    {
        int mid = start + (end - start) / 2;
        return new Node(build(start, mid), build(mid + 1, end));
    }
}
Node *update(Node *node, int start, int end, int pos, int val)
{
    if (start == end)
    {
        return new Node(val);
    }
    else
    {
        int mid = start + (end - start) / 2;
        if (start <= pos && mid >= pos)
        {
            return new Node(update(node->left, start, mid, pos, val), node->right);
        }
        else
        {
            return new Node(node->left, update(node->right, mid + 1, end, pos, val));
        }
    }
}

int query(Node *past, Node *pres, int start, int end, int k)
{
    if (start == end)
    {
        return start;
    }
    else
    {
        int mySegCount = pres->left->sum - past->left->sum;
        if (k <= mySegCount)
        {
            return query(past->left, pres->left, start, start + (end - start) / 2, k);
        }
        else
        {
            return query(past->right, pres->right, start + 1 + (end - start) / 2, end, k - mySegCount);
        }
    }
}
int main()
{

    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, q;
    cin >> n;
    cin >> q;
    vector<int> arr(n);
    vector<Node *> states;
    states.push_back(build(0, n - 1));

    for (int i = 0; i < n; i++)
    {
        cin >> arr[i];
    }
    vector<pair<int, int>> sorted(n);
    for (int i = 0; i < n; i++)
    {
        sorted[i].first = arr[i];
        sorted[i].second = i;
    }
    sort(sorted.begin(), sorted.end());

    vector<int> IndxinTree(n);
    for (int i = 0; i < n; i++)
    {
        IndxinTree[sorted[i].second] = i;
    }
    for (int i = 0; i < n; i++)
    {
        Node *root = update(states[states.size() - 1], 0, n - 1, IndxinTree[i], 1);
        states.push_back(root);
    }
    while (q--)
    {
        int l, r, k;
        cin >> l >> r >> k;
        l--, r--;
        int sortpos = query(states[l], states[r + 1], 0, n - 1, k);
        cout << sorted[sortpos].first << endl;
    }
}