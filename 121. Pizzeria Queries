#include <iostream>
#include <vector>
#include <algorithm>
#include <cstdio>
using namespace std;
#define int long long
class Segment
{
    vector<int> a;
    int n;
    int getMin(int i, int tl, int tr, int l, int r)
    {
        if (l > r)
            return 1e18;
        else if (tl == l && tr == r)
            return a[i];
        int tm = (tl + tr) >> 1;
        return min(getMin(i << 1, tl, tm, l, min(r, tm)), getMin(i << 1 | 1, tm + 1, tr, max(l, tm + 1), r));
    }
    void update(int i, int tl, int tr, int pos, int delta)
    {
        if (tl == tr)
            a[i] += delta;
        else
        {
            int tm = (tl + tr) >> 1;
            if (pos <= tm)
                update(i << 1, tl, tm, pos, delta);
            else
                update(i << 1 | 1, tm + 1, tr, pos, delta);
            a[i] = min(a[i << 1], a[i << 1 | 1]);
        }
    }

public:
    Segment(int nn) : a(nn << 2), n(nn) {}
    int getMin(int l, int r)
    {
        return getMin(1, 0, n - 1, l, r);
    }
    void update(int pos, int delta)
    {
        update(1, 0, n - 1, pos, delta);
    }
};
signed main()
{
#ifdef LOCAL
    freopen("input.txt", "r", stdin);
#endif
    int n,
        q;
    cin >> n >> q;
    vector<int> a(n);
    for (auto &x : a)
        cin >> x;
    Segment left(n), right(n);
    for (int i = 0; i < n; i++)
        left.update(i, a[i] - i), right.update(i, a[i] + i);
    while (q--)
    {
        int t;
        cin >> t;
        if (t == 2)
        {
            int pos;
            cin >> pos;
            pos--;
            int ans = min(left.getMin(0, pos) + pos, right.getMin(pos, n - 1) - pos);
            cout << ans << endl;
        }
        else
        {
            int pos, x;
            cin >> pos >> x;
            pos--;
            int delta = x - a[pos];
            a[pos] = x;
            left.update(pos, delta), right.update(pos, delta);
        }
    }
}
