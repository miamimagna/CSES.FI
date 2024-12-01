#include <iostream>
#include <algorithm>
#include <vector>
#include <cstdio>
using namespace std;
#define int long long
class Segment
{
    vector<int> a, b;
    int n;
    void build(vector<int> &arr, int i, int l, int r)
    {
        if (l == r)
            a[i] = arr[l];
        else
        {
            int mid = (l + r) >> 1;
            build(arr, i << 1, l, mid);
            build(arr, i << 1 | 1, mid + 1, r);
            a[i] = max(a[i << 1], a[i << 1 | 1]);
        }
    }
    void push(int i)
    {
        b[i << 1] += b[i];
        b[i << 1 | 1] += b[i];
        a[i] += b[i];
        b[i] = 0;
    }
    int getMax(int i, int tl, int tr, int l, int r)
    {
        if (l > r)
            return -1e18;
        else if (tl == l && tr == r)
            return a[i] + b[i];
        push(i);
        int mid = (tl + tr) >> 1;
        return max(getMax(i << 1, tl, mid, l, min(r, mid)), getMax(i << 1 | 1, mid + 1, tr, max(l, mid + 1), r));
    }
    void update(int i, int tl, int tr, int l, int r, int delta)
    {
        if (l > r)
            return;
        else if (tl == l && tr == r)
            b[i] += delta;
        else
        {
            int tm = (tl + tr) >> 1;
            update(i << 1, tl, tm, l, min(r, tm), delta);
            update(i << 1 | 1, tm + 1, tr, max(l, tm + 1), r, delta);
            a[i] = max(a[i << 1] + b[i << 1], a[i << 1 | 1] + b[i << 1 | 1]);
        }
    }

public:
    Segment(int nn) : a(nn << 2), b(nn << 2), n(nn) {}
    Segment(vector<int> &arr) : Segment((int)arr.size())
    {
        build(arr, 1, 0, n - 1);
    }
    int getMax(int l, int r)
    {
        return getMax(1, 0, n - 1, l, r);
    }
    void update(int l, int r, int delta)
    {
        update(1, 0, n - 1, l, r, delta);
    }
};
signed main()
{
#ifdef LOCAL
    freopen("input.txt", "r", stdin);
#endif
    int n, q;
    cin >> n >> q;
    vector<int> a(n);
    for (auto &x : a)
        cin >> x;
    vector<int> prefix(n + 1);
    for (int i = 1; i <= n; i++)
        prefix[i] = prefix[i - 1] + a[i - 1];
    Segment st(prefix);
    while (q--)
    {
        int t, x, y;
        cin >> t >> x >> y;
        if (t == 1)
        {
            int delta = y - a[x - 1];
            a[x - 1] = y;
            st.update(x, n, delta);
        }
        else
        {
            cout << max(0ll, st.getMax(x, y) - st.getMax(x - 1, x - 1)) << endl;
        }
    }
}
