#include <iostream>
#include <vector>
#include <cstdio>
using namespace std;
#define int long long
class Fenwick0
{
    int g(int x)
    {
        return x & (x + 1);
    }
    int h(int x)
    {
        return x | (x + 1);
    }
    vector<int> a;
    int n;

public:
    explicit Fenwick0(size_t N) : n(N), a(N) {}
    Fenwick0(vector<int> &arr) : Fenwick0(arr.size())
    {
        for (int i = 0; i < arr.size(); i++)
        {
            a[i] += arr[i];
            if (h(i) < n)
                a[h(i)] += a[i];
        }
    }
    long long sum(int i)
    {
        int res = 0;
        for (; i >= 0; i = g(i) - 1)
            res += a[i];
        return res;
    }
    void add(int i, int delta)
    {
        for (; i < n; i = h(i))
            a[i] += delta;
    }
};
signed main()
{
    int n;
    cin >> n;
    vector<int> a(n), temp(n, 1);
    for (auto &x : a)
        cin >> x;
    Fenwick0 f(temp);
    while (n--)
    {
        int x;
        cin >> x;
        int ans = -1, hi = (int)a.size() - 1, lo = 0;
        while (hi >= lo)
        {
            int mid = (hi + lo) >> 1;
            if (f.sum(mid) >= x)
                ans = mid, hi = mid - 1;
            else
                lo = mid + 1;
        }
        if (ans != -1)
        {
            f.add(ans, -1);
        }
        cout << a[ans] << ' ';
    }
    cout << endl;
}
