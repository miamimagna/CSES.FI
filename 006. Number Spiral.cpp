#include <iostream>
using namespace std;
#define int long long
signed main()
{
    ios::sync_with_stdio(NULL);
    cin.tie(0);
    int q;
    cin >> q;
    while (q--)
    {
        int x, y;
        cin >> x >> y;
        if (max(x, y) & 1)
            swap(x, y);
 
        if (x > y)
            cout << x * x - y + 1 << "\n";
        else
            cout << (y - 1) * (y - 1) + x << "\n";
    }
}
