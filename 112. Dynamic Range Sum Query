#include <iostream>
#include <vector>
#include <algorithm>
#include <cstdio>
using namespace std;
#define int long long
class Fenwick
{
    vector<int> a;
    int n;

public:
    Fenwick(int nn) : a(nn + 1), n(nn) {}
    Fenwick(vector<int> &arr) : Fenwick((int)arr.size())
    {
        for (int i = 1; i <= n; i++)
        {
            a[i] += arr[i - 1];
            int j = i + (i & -i);
            if (j <= n)
                a[j] += a[i];
        }
    }
    int sum(int i)
    {
        int res = 0;
        for (i++; i > 0; i -= i & -i)
            res += a[i];
        return res;
    }
    void update(int i, int delta)
    {
        for (i++; i <= n; i += i & -i)
            a[i] += delta;
    }
    int sum(int l, int r)
    {
        return sum(r) - sum(l - 1);
    }
    void replace(int i, int x)
    {
        int delta = x - sum(i, i);
        update(i, delta);
    }
};
signed main()
{
    int n, q;
    cin >> n >> q;
    vector<int> a(n);
    for (auto &x : a)
        cin >> x;
    Fenwick f(a);
    while (q--)
    {
        int tp, aa, b;
        cin >> tp >> aa >> b;
        if (tp == 1)
        {
            int k, u;
            k = aa, u = b;
            k--;
            f.replace(k, u);
        }
        else
        {
            int l = aa, r = b;
            l--, r--;
            cout << f.sum(l, r) << endl;
        }
    }
}
