#include <iostream>
#include <vector>
#include <cstdio>
using namespace std;
#define int long long
signed main()
{
    int n, q;
    cin >> n >> q;
    vector<int> a(n + 1);
    cin >> a[1];
    for (int x{}, i = 1; i < n; i++)
    {
        cin >> x;
        a[i + 1] = a[i] + x;
    }
    while (q--)
    {
        int l, b;
        cin >> l >> b;
        l--;
        cout << a[b] - a[l] << endl;
    }
}
