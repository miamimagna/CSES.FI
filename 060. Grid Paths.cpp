#include <cstdio>
#include <iostream>
#include <vector>
#include <string>
using namespace std;
// preprocessing to make code easier
template <typename T>
using v = vector<T>;
int mod = 1e9 + 7;
// memoisation
int generate_memo(int i, int j, v<v<char>>& grid, int n, v<v<int>>& dp){
    if(i < 0 || j < 0 || i == n || j == n) return 0;
    if(grid[i][j] == '*') return 0;
    if(i == n - 1 && j == n - 1) return 1;
    if(dp[i][j] != -1) return dp[i][j];
    dp[i][j] = 0;
    return dp[i][j] = (generate_memo(i + 1, j, grid, n, dp) + generate_memo(i, j + 1, grid, n, dp)) % mod;
}
// tabulation
int generate_tabulation(int i, int j, v<v<char>> &grid, int n, v<v<int>> &dp){
    for(int i = n - 1; i >= 0; i--)
        for(int j = n - 1; j >= 0; j--)
            if(grid[i][j] == '*') continue;
            else if(i == n - 1 && j == n - 1) dp[i][j] = grid[i][j] == '.';
            else {
                if(i != n - 1)
                    dp[i][j] = dp[i + 1][j];
                if(j != n - 1)
                    dp[i][j] += dp[i][j + 1];
                dp[i][j] %= mod;
            }
    return dp[0][0];
}
// space optimized O(n)
int generate(int i, int j, v<v<char>>& grid, int n, v<int>& dp){
    for (int i = n - 1; i >= 0; i--)
        for (int j = n - 1; j >= 0; j--)
            if (grid[i][j] == '*')
                dp[j] = 0;
            else if (i == n - 1 && j == n - 1)
                dp[j] = grid[i][j] == '.';
            else
            {
                int temp = dp[j];
                dp[j] = 0;
                if (i != n - 1)
                    dp[j] = temp;
                if (j != n - 1)
                    dp[j] += dp[j + 1];
                dp[j] %= mod;
            }
    return dp[0];
}
void solve()
{
    int n; cin >> n;
    v<v<char>> a(n, v<char>(n));
    for(auto &x: a)
        for(auto &y: x)
            cin >> y;
    v<int> dp(n);
    cout << generate(0, 0, a, n, dp) << endl;
}
int main()
{
#ifdef LOCAL
    freopen("input.txt", "r", stdin);
#endif
    solve();
}
