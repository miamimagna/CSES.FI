#include <iostream>
#include <vector>
using namespace std;
template <typename t>
using v = vector<t>;
int mod = 1e9 + 7;
int dp[1 << 21][21];
signed main()
{
#ifdef LOCAL
    freopen("input.txt", "r", stdin);
#else
    ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);
#endif
    int n, m;
    cin >> n >> m;
    v<v<int>> adj(n);
    while (m--)
    {
        int x, y;
        cin >> x >> y;
        x--, y--;
        adj[x].push_back(y);
    }
    dp[1][0] = 1;
    for (int i = 1; i < (1 << n); i++)
        for (int j = 0; j < n; j++)
            if (dp[i][j])
                for (int child : adj[j])
                    if (!((1 << child) & i))
                        dp[(1 << child) ^ i][child] = (dp[(1 << child) ^ i][child] + dp[i][j]) % mod;
    cout << dp[(1 << n) - 1][n - 1] << endl;
}
