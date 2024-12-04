#include <iostream>
#include <vector>
#include <cstdio>
#include <algorithm>
#include <utility>
using namespace std;
#define int long long
#define aa first
#define dd second
class Segment
{
    vector<int> a;
    vector<pair<int, int>> b;
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
            a[i] = a[i << 1] + a[i << 1 | 1];
        }
    }
    void push(int i, int l, int r)
    {
        if (b[i].aa)
        {
            if (l == r)
            {
                a[i] += b[i].aa;
                b[i] = {0, 0};
            }
            else
            {
                int mid = (l + r) >> 1;
                int num = (r - l + 1);
                b[i << 1].aa += b[i].aa;
                b[i << 1].dd += b[i].dd;
                b[i << 1 | 1].aa += b[i].aa + (mid - l + 1) * b[i].dd;
                b[i << 1 | 1].dd += b[i].dd;
                a[i] += num * (2 * b[i].aa + (num - 1) * b[i].dd) / 2;
                b[i] = {0, 0};
            }
        }
    }
    int sum(int i, int tl, int tr, int l, int r)
    {
        if (l > r)
            return 0;
        push(i, tl, tr);
        if (tl == l && tr == r)
            return a[i];
        else
        {
            int tm = (tl + tr) >> 1;
            return sum(i << 1, tl, tm, l, min(tm, r)) + sum(i << 1 | 1, tm + 1, tr, max(l, tm + 1), r);
        }
    }
    void update(int i, int tl, int tr, int l, int r, int val)
    {
        if (l > r)
            return;
        push(i, tl, tr);
        if (tl == l && tr == r)
            b[i] = {val, 1};
        else
        {
            int tm = (tl + tr) >> 1;
            update(i << 1, tl, tm, l, min(r, tm), val);
            update(i << 1 | 1, tm + 1, tr, max(l, tm + 1), r, val + (max(tm, l - 1) - l + 1));
            push(i << 1, tl, tm);
            push(i << 1 | 1, tm + 1, tr);
            a[i] = a[i << 1] + a[i << 1 | 1];
        }
    }

public:
    Segment(int n) : a(n << 2), b(n << 2), n(n) {}
    Segment(vector<int> &arr) : Segment((int)arr.size())
    {
        build(arr, 1, 0, n - 1);
    }
    int sum(int l, int r)
    {
        return sum(1, 0, n - 1, l, r);
    }
    void update(int l, int r, int val)
    {
        update(1, 0, n - 1, l, r, val);
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
    Segment st(a);
    while (q--)
    {
        int type;
        cin >> type;
        if (type == 2)
        {
            int l, r;
            cin >> l >> r;
            l--, r--;
            cout << st.sum(l, r) << endl;
        }
        else
        {
            int l, r;
            cin >> l >> r;
            l--, r--;
            st.update(l, r, 1);
        }
    }
}
