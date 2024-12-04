#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
#define int long long
class Seggs
{
    vector<vector<int>> a;
    int n, m;
    void build_y(vector<vector<int>> &arr, int ix, int lx, int rx, int iy, int ly, int ry)
    {
        if (ly == ry)
        {
            if (lx == rx)
                a[ix][iy] = arr[lx][ly];
            else
                a[ix][iy] = a[ix << 1][iy] + a[ix << 1 | 1][iy];
        }
        else
        {
            int mid = (ly + ry) >> 1;
            build_y(arr, ix, lx, rx, iy << 1, ly, mid);
            build_y(arr, ix, lx, rx, iy << 1 | 1, mid + 1, ry);
            a[ix][iy] = a[ix][iy << 1] + a[ix][iy << 1 | 1];
        }
    }
    void build_x(vector<vector<int>> &arr, int i, int l, int r)
    {
        if (l != r)
        {
            int mid = (l + r) >> 1;
            build_x(arr, i << 1, l, mid);
            build_x(arr, i << 1 | 1, mid + 1, r);
        }
        build_y(arr, i, l, r, 1, 0, m - 1);
    }
    int sum_y(int ix, int iy, int tl, int tr, int l, int r)
    {
        if (l > r)
            return 0;
        if (tl == l && tr == r)
            return a[ix][iy];
        int mid = (tl + tr) >> 1;
        return sum_y(ix, iy << 1, tl, mid, l, min(r, mid)) + sum_y(ix, iy << 1 | 1, mid + 1, tr, max(l, mid + 1), r);
    }
    int sum_x(int i, int tl, int tr, int lx, int rx, int ly, int ry)
    {
        if (lx > rx)
            return 0;
        if (tl == lx && tr == rx)
            return sum_y(i, 1, 0, m - 1, ly, ry);
        int mid = (tr + tl) >> 1;
        return sum_x(i << 1, tl, mid, lx, min(rx, mid), ly, ry) + sum_x(i << 1 | 1, mid + 1, tr, max(lx, mid + 1), rx, ly, ry);
    }
    void update_y(int ix, int iy, int tl, int tr, int pos, int delta)
    {
        if (tl == tr)
            a[ix][iy] += delta;
        else
        {
            int mid = (tl + tr) >> 1;
            if (pos <= mid)
                update_y(ix, iy << 1, tl, mid, pos, delta);
            else
                update_y(ix, iy << 1 | 1, mid + 1, tr, pos, delta);
            a[ix][iy] = a[ix][iy << 1] + a[ix][iy << 1 | 1];
        }
    }
    void update_x(int i, int tl, int tr, int posx, int posy, int delta)
    {
        if (tl != tr)
        {
            int mid = (tl + tr) >> 1;
            if (posx <= mid)
                update_x(i << 1, tl, mid, posx, posy, delta);
            else
                update_x(i << 1 | 1, mid + 1, tr, posx, posy, delta);
        }
        update_y(i, 1, 0, m - 1, posy, delta);
    }

public:
    Seggs(int nn, int mm) : n(nn), m(mm), a(nn << 2, vector<int>(mm << 2)) {}
    Seggs(vector<vector<int>> &arr) : Seggs((int)arr.size(), (int)arr[0].size())
    {
        build_x(arr, 1, 0, n - 1);
    }
    int sum(int lx, int rx, int ly, int ry)
    {
        return sum_x(1, 0, n - 1, lx, rx, ly, ry);
    }
    void update(int x, int y, int delta)
    {
        update_x(1, 0, n - 1, x, y, delta);
    }
};
signed main()
{
#ifdef LOCAL
    freopen("input.txt", "r", stdin);
#endif
    int n, q;
    cin >> n >> q;
    vector<vector<int>> a(n, vector<int>(n));
    for (auto &x : a)
        for (auto &y : x)
        {
            char ch;
            cin >> ch;
            y = ch == '*';
        }
    Seggs st(a);
    while (q--)
    {
        int t;
        cin >> t;
        if (t == 1)
        {
            int x, y;
            cin >> x >> y;
            x--, y--;
            int cur = st.sum(x, x, y, y);
            int delta = cur == 0 ? 1 : -1;
            st.update(x, y, delta);
        }
        else
        {
            int l1, l2, r1, r2;
            cin >> l1 >> r1 >> l2 >> r2;
            l1--, l2--, r1--, r2--;
            cout << st.sum(l1, l2, r1, r2) << endl;
        }
    }
}
