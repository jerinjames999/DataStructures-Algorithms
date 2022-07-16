#include <bits/stdc++.h>
using namespace std;

class Segment_Tree
{
    int *SegArray, SegSize, n;

public:
    Segment_Tree(vector<int> &arr)
    {
        n = arr.size();
        int power = (int)(log2(n));
        if (log2(n) == power)
            power++;
        else
        {
            power = power + 2;
        }
        SegSize = (1 << power);
        SegArray = new int[SegSize];
        BuildTree(0, 0, n - 1, arr);
        cout << endl;
        for (int i = 0; i < SegSize; i++)
        {
            cout << i << " - " << SegArray[i] << endl;
        }
    }
    void BuildTree(int si, int ss, int se, vector<int> &arr)
    {
        cout << "{" << si << " " << ss << " " << se << "}" << endl;
        if (ss == se)
        {
            cout << "Hi"<<endl;
            SegArray[si] = arr[ss];
            return;
        }
        int mid = ss + (se - ss) / 2;
        BuildTree(2 * si + 1, ss, mid, arr);
        BuildTree(2 * si + 2, mid + 1, se, arr);
        SegArray[si] = Merge(2 * si + 1, 2 * si + 2);
    }
    int Merge(int l, int r)
    {
        return min(SegArray[l], SegArray[r]);
    }
    int MergeResult(int lv, int rv)
    {
        return min(lv, rv);
    }
    int RangeQuery(int si, int ss, int se, int qs, int qe)
    {
        if (qs > se || qe < ss)
            return INT_MAX;
        if (qs <= ss && qe >= se)
            return SegArray[si];
        int mid = ss + (se - ss) / 2;
        int lv = RangeQuery(2 * si + 1, ss, mid, qs, qe);
        int rv = RangeQuery(2 * si + 2, mid + 1, se, qs, qe);
        return MergeResult(lv, rv);
    }
    void Update(int si, int ss, int se, int idx, int val)
    {
        if (ss == se)
        {
            SegArray[si] = val;
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
            SegArray[si] = Merge(2 * si + 1, 2 * si + 2);
        }
    }
    ~Segment_Tree()
    {
        delete[] SegArray;
    }
};

int main()
{

    int n;
    cin >> n;
    vector<int> arr(n);
    for (int i = 0; i < n; i++)
    {
        cin >> arr[i];
    }
    Segment_Tree Seg(arr);
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
            cout << "RangeQuery(" << Query[i][1] << ", " << Query[i][2] << ")   :   " << Seg.RangeQuery(0, 0, n - 1, Query[i][1], Query[i][2]) << endl;
        }
    }

    return 0;
}
