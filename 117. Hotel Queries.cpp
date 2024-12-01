#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>
#include <cstdio>
using namespace std;
class SegTreeRecur
{
    vector<int> a;
    int n;
    void build(vector<int> &arr, int idx, int l, int r)
    {
        if (l == r)
            a[idx] = arr[l];
        else
        {
            int mid = (l + r) >> 1;
            build(arr, idx << 1, l, mid);
            build(arr, idx << 1 | 1, mid + 1, r);
            a[idx] = max(a[idx << 1], a[idx << 1 | 1]);
        }
    }
    int sumHelper(int idx, int l, int r, int tl, int tr)
    {
        if (l > r)
            return 0;
        else if (tl == l && tr == r)
            return a[idx];
        else
        {
            int mid = (tl + tr) >> 1;
            return max(sumHelper(idx << 1, l, min(r, mid), tl, mid), sumHelper(idx << 1 | 1, max(mid + 1, l), r, mid + 1, tr));
        }
    }
    void increaseHelper(int i, int idx, int x, int l, int r)
    {
        if (l == r)
        {
            a[i] += x;
            return;
        }
        else if (idx <= (l + r) >> 1)
            increaseHelper(2 * i, idx, x, l, (l + r) >> 1);
        else
            increaseHelper(2 * i + 1, idx, x, ((l + r) >> 1) + 1, r);
        a[i] = max(a[2 * i], a[2 * i + 1]);
    }

public:
    SegTreeRecur(int nn) : a(4 * nn), n(nn) {}
    SegTreeRecur(vector<int> &arr) : SegTreeRecur((int)arr.size())
    {
        build(arr, 1, 0, arr.size() - 1);
    }
    int sum(int l, int r)
    {
        return sumHelper(1, l, r, 0, n - 1);
    }
    void increase(int i, int inc)
    {
        increaseHelper(1, i, inc, 0, n - 1);
    }
};
#include <cstdio>
int main()
{
#ifdef LOCAL
    freopen("input.txt", "r", stdin);
#endif
    int n, q;
    cin >> n >> q;
    vector<int> a(n), queries(q);
    for (auto &x : a)
        cin >> x;
    for (auto &x : queries)
        cin >> x;
    SegTreeRecur st(a);
    for (int i = 0; i < q; i++)
    {
        int x = queries[i], ans = -1;
        int hi = n - 1, lo = 0;
        while (hi >= lo)
        {
            int mid = (hi + lo) >> 1;
            if (st.sum(0, mid) >= x)
                ans = mid, hi = mid - 1;
            else
                lo = mid + 1;
        }
        if (ans != -1)
            st.increase(ans, -x);
        cout << ans + 1 << ' ';
    }
    cout << endl;
}
