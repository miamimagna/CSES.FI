#include <iostream>
#include <vector>
#include <algorithm>
#include <cstdio>
using namespace std;
class SegMin
{
    vector<int> a;
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
            a[i] = min(a[i << 1], a[i << 1 | 1]);
        }
    }
    int getMin(int i, int tl, int tr, int l, int r)
    {
        if (l > r)
            return 1e9 + 1;
        else if (tl == l && tr == r)
            return a[i];
        int tm = (tl + tr) >> 1;
        return min(getMin(i << 1, tl, tm, l, min(r, tm)), getMin(i << 1 | 1, tm + 1, tr, max(l, tm + 1), r));
    }
    void update(int i, int tl, int tr, int pos, int x)
    {
        if (tl == tr)
            a[i] = x;
        else
        {
            int tm = (tl + tr) >> 1;
            if (pos <= tm)
                update(i << 1, tl, tm, pos, x);
            else
                update(i << 1 | 1, tm + 1, tr, pos, x);
            a[i] = min(a[i << 1], a[i << 1 | 1]);
        }
    }

public:
    SegMin(int nn) : a(nn << 2), n(nn) {}
    SegMin(vector<int> &arr) : SegMin((int)arr.size())
    {
        build(arr, 1, 0, n - 1);
    }
    int getMin(int l, int r)
    {
        return getMin(1, 0, n - 1, l, r);
    }
    void update(int pos, int x)
    {
        update(1, 0, n - 1, pos, x);
    }
};
int main()
{
    int n, q;
    cin >> n >> q;
    vector<int> a(n);
    for (auto &x : a)
        cin >> x;
    SegMin st(a);
    while (q--)
    {
        int tp, a, b;
        cin >> tp >> a >> b;
        if (tp == 1)
            st.update(a - 1, b);
        else
            cout << st.getMin(a - 1, b - 1) << endl;
    }
}
