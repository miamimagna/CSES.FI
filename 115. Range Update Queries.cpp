#include <iostream>
#include <vector>
#include <cstdio>
using namespace std;
#define int long long
class Segment
{
    vector<int> a;
    int n;
    void push(int i)
    {
        a[i << 1] += a[i];
        a[i << 1 | 1] += a[i];
        a[i] = 0;
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
        }
    }
    int query(int i, int tl, int tr, int pos)
    {
        if (tl == tr)
            return a[i];
        else
        {
            push(i);
            int mid = (tl + tr) >> 1;
            if (pos <= mid)
                return query(i << 1, tl, mid, pos);
            else
                return query(i << 1 | 1, mid + 1, tr, pos);
        }
    }
    void update(int i, int tl, int tr, int l, int r, int x)
    {
        if (l > r)
            return;
        else if (tl == l && tr == r)
            a[i] += x;
        else
        {
            int tm = (tl + tr) >> 1;
            update(i << 1, tl, tm, l, min(r, tm), x);
            update(i << 1 | 1, tm + 1, tr, max(l, tm + 1), r, x);
        }
    }

public:
    Segment(int nn) : a(nn << 2), n(nn) {}
    Segment(vector<int> &arr) : Segment((int)arr.size())
    {
        build(arr, 1, 0, n - 1);
    }
    int query(int i)
    {
        return query(1, 0, n - 1, i);
    }
    void update(int l, int r, int x)
    {
        update(1, 0, n - 1, l, r, x);
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
            int i;
            cin >> i;
            cout << st.query(i - 1) << endl;
        }
        else
        {
            int l, r, x;
            cin >> l >> r >> x;
            st.update(l - 1, r - 1, x);
        }
    }
}
