#include <iostream>
#include <vector>
#include <algorithm>
#include <cstdio>
using namespace std;
#define int long long
class SegTreeMaxSum 
{
    struct Node
    {
        int sum, suffix, prefix, max_sum;
        explicit Node(int x) : sum(x), suffix(x), prefix(x), max_sum(x) {}
        Node() = default;
        Node operator+(Node right)
        {
            Node parent, &left = *this;
            parent.sum = left.sum + right.sum;
            parent.prefix = max(left.prefix, left.sum + right.prefix);
            parent.suffix = max(right.suffix, right.sum + left.suffix);
            parent.max_sum = max(left.max_sum, max(right.max_sum, left.suffix + right.prefix));
            return parent;
        }
    };
    vector<Node> a;
    int n;
    void build(vector<int> &arr, int idx, int l, int r)
    {
        if (l == r)
            a[idx] = Node(arr[l]);
        else
        {
            int mid = (l + r) >> 1;
            build(arr, idx << 1, l, mid);
            build(arr, idx << 1 | 1, mid + 1, r);
            a[idx] = a[idx << 1] + a[idx << 1 | 1];
        }
    }
    int sumHelper(int idx, int l, int r, int tl, int tr)
    {
        if (l > r)
            return 0;
        else if (tl == l && tr == r)
            return a[idx].sum;
        else
        {
            int mid = (tl + tr) >> 1;
            return sumHelper(idx << 1, l, min(r, mid), tl, mid) + sumHelper(idx << 1 | 1, max(mid + 1, l), r, mid + 1, tr);
        }
    }
    void replaceHelper(int i, int idx, int x, int l, int r)
    {
        if (l == r)
        {
            a[i] = Node(x);
            return;
        }
        else if (idx <= (l + r) >> 1)
            replaceHelper(2 * i, idx, x, l, (l + r) >> 1);
        else
            replaceHelper(2 * i + 1, idx, x, ((l + r) >> 1) + 1, r);
        a[i] = a[2 * i] + a[2 * i + 1];
    }
    Node query(int v, int tl, int tr, int l, int r)
    {
        if (l > r)
            return Node(-1e9);
        if (l == tl && r == tr)
            return a[v];
        int tm = (tl + tr) >> 1;
        return query(v << 1, tl, tm, l, min(r, tm)) + query(v << 1 | 1, tm + 1, tr, max(l, tm + 1), r);
    }
 
public:
    SegTreeMaxSum(int nn) : a(4 * nn), n(nn) {}
    SegTreeMaxSum(vector<int> &arr) : SegTreeMaxSum((int)arr.size())
    {
        build(arr, 1, 0, arr.size() - 1);
    }
    int sum(int l, int r)
    {
        return sumHelper(1, l, r, 0, n - 1);
    }
    void replace(int idx, int x)
    {
        replaceHelper(1, idx, x, 0, n - 1);
    }
    int getMax(int l, int r)
    {
        return query(1, 0, n - 1, l, r).max_sum;
    }
};
signed main()
{
    int n, q;
    cin >> n >> q;
    vector<int> a(n);
    for (auto &x : a)
        cin >> x;
    SegTreeMaxSum st(a);
    while (q--)
    {
        int pos, x;
        cin >> pos >> x;
        pos--;
        st.replace(pos, x);
        int res = st.getMax(0, n - 1);
        cout << (res >= 0 ? res : 0) << endl;
    }
}
