#include <iostream>
#include <algorithm>
#include <vector>
#include <cstdio>
using namespace std;
#define int long long
class Segment
{
    vector<int> a, b;
    vector<bool> updated;
    int n;
    int get(int i, int l, int r)
    {
        push(i, l, r);
        return a[i];
    }
    void push(int i, int l, int r)
    {
        if (l == r && b[i])
            a[i] += b[i], b[i] = 0, updated[i] = 0;
        else if (l != r)
        {
            if (updated[i])
            {
                updated[i << 1] = updated[i << 1 | 1] = 1;
                b[i << 1] = b[i << 1 | 1] = 0;
                a[i << 1] = a[i << 1 | 1] = a[i];
                updated[i] = 0;
                a[i] *= (r - l + 1);
            }
            if (b[i])
            {
                b[i << 1] += b[i];
                b[i << 1 | 1] += b[i];
                a[i] += b[i] * (r - l + 1);
                b[i] = 0;
            }
        }
    }
    void build(vector<int> &arr, int i, int l, int r)
    {
        if (l == r)
            a[i] = arr[l];
        else
        {
            int mid = (l + r) >> 1;
            build(arr, i << 1, l, mid);
            build(arr, i << 1 | 1, mid + 1, r);
            a[i] = a[i << 1] + a[i << 1 | 1];
        }
    }
    int sum(int i, int tl, int tr, int l, int r)
    {
        if (l > r)
            return 0;
        push(i, tl, tr);
        if (tl == l && tr == r)
            return a[i];
        int tm = (tl + tr) >> 1;
        return sum(i << 1, tl, tm, l, min(r, tm)) + sum(i << 1 | 1, tm + 1, tr, max(tm + 1, l), r);
    }
    void update(int i, int tl, int tr, int l, int r, int delta)
    {
        if (l > r)
            return;
        push(i, tl, tr);
        if (tl == l && tr == r)
            b[i] += delta;
        else
        {
            int tm = (tl + tr) >> 1;
            update(i << 1, tl, tm, l, min(r, tm), delta);
            update(i << 1 | 1, tm + 1, tr, max(l, tm + 1), r, delta);
            a[i] = get(i << 1, tl, tm) + get(i << 1 | 1, tm + 1, tr);
        }
    }
    void replace(int i, int tl, int tr, int l, int r, int val)
    {
        if (l > r)
            return;
        push(i, tl, tr);
        if (tl == l && tr == r)
            b[i] = 0, updated[i] = 1, a[i] = val;
        else
        {
            int tm = (tl + tr) >> 1;
            replace(i << 1, tl, tm, l, min(r, tm), val);
            replace(i << 1 | 1, tm + 1, tr, max(l, tm + 1), r, val);
            a[i] = get(i << 1, tl, tm) + get(i << 1 | 1, tm + 1, tr);
        }
    }
 
public:
    Segment(int nn) : a(nn << 2), b(nn << 2), updated(nn << 2), n(nn) {}
    Segment(vector<int> &arr) : Segment((int)arr.size())
    {
        build(arr, 1, 0, n - 1);
    }
    int sum(int l, int r)
    {
        return sum(1, 0, n - 1, l, r);
    }
    void update(int l, int r, int delta)
    {
        update(1, 0, n - 1, l, r, delta);
    }
    void replace(int l, int r, int val)
    {
        replace(1, 0, n - 1, l, r, val);
    }
};
signed main()
{
#ifdef LOCAL
    freopen("input.txt", "r", stdin);
#endif
    ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);
    int n, q;
    cin >> n >> q;
    vector<int> a(n);
    for (auto &x : a)
        cin >> x;
    Segment st(a);
    while (q--)
    {
        int t, l, r;
        cin >> t >> l >> r;
        l--, r--;
        if (t == 3)
            cout << st.sum(l, r) << endl;
        else
        {
            int x;
            cin >> x;
            t == 1 ? st.update(l, r, x) : st.replace(l, r, x);
        }
    }
}
