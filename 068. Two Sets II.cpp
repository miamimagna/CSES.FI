#include <cstdio>
#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
using namespace std;
// preprocessing to make code easier
template <typename T>
using v = vector<T>;
#define sz size()
#define int long long
int mod = 1e9 + 7;
int gcd(int a, int b, int &x, int &y)
{
    if (b == 0)
    {
        x = 1, y = 0;
        return a;
    }
    int x1, y1;
    int res = gcd(b, a % b, x1, y1);
    x = y1;
    y = x1 - y1 * (a / b);
    return res;
}
int mod_inv(int a, int m)
{
    int x, y;
    int g = gcd(a, m, x, y);
    if (g != 1)
    {
        cout << "not Possible" << endl;
        return -1e18;
    }
    else
        return (x % m + m) % m;
}
void solve()
{
    int n;
    cin >> n;
    int sum = n * (n + 1) / 2;
    v<int> dp(sum + 1), prev(sum + 1);
    dp[0] = prev[0] = 1;
    for (int i = 1; i < n; i++, prev = dp)
    {
        for (int j = 0; j + i < sum; j++)
            dp[j + i] = (prev[j + i] + prev[j]) % mod;
    }
    cout << (sum % 2 == 0 ? dp[sum / 2] : 0) << endl;
}
signed main()
{
    solve();
}
