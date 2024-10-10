#include <cstdio>
#include <iostream>
#include <vector>
#include <string>
using namespace std;
// preprocessing to make code easier
template <typename T>
using v = vector<T>;
#define sz size()
#define int long long
int mod = 1e9 + 7;
int generate_memoization(int i, int j, const string& a, const string& b, int an, int bn, v<v<int>> &dp){
    if(i == an && j == bn) return 0;
    if(i == an || j == bn) return (an + bn - i - j);
    if(a[i] == b[j]) return generate_memoization(i + 1, j + 1, a, b, an, bn, dp);
    if(dp[i][j] != 1E9) return dp[i][j];
    dp[i][j] = min(1 + generate_memoization(i + 1, j, a, b, an, bn, dp), 
                       min(1 +generate_memoization(i, j + 1, a, b, an, bn, dp), 
                           1 + generate_memoization(i + 1, j + 1, a, b, an, bn, dp)));
    return dp[i][j];
}
int generate_space_optimized(const string &a, const string& b, int an, int bn){
    v<int> dp(bn + 1, 1e9), prev(dp);
    for(int i = bn, j = 0; i >= 0; i--, j++)
        prev[i] = j;
    for(int i = an - 1; i >= 0; i--, prev = dp){
        dp.back() = an - i;
        for(int j = bn - 1; j >= 0; j--){
            dp[j] = 1e9;
            if(a[i] == b[j]) dp[j] = prev[j + 1];
            else dp[j]  = min(1 + prev[j], min(1 + dp[j + 1], 1 + prev[j + 1]));
        }
    }
    return dp[0];
}
int generate_tabulation(const string& a, const string& b){
    v<v<int>> dp(a.sz + 1, v<int>(b.sz + 1, 1E9));
    for (int i = 0; i <= a.sz; i++)
        dp[i][b.sz] = a.sz - i;
    for (int i = 0; i <= b.sz; i++)
        dp[a.sz][i] = b.sz - i;
    for (int i = a.sz - 1; i >= 0; i--)
        for (int j = b.sz - 1; j >= 0; j--)
        {
            if (a[i] == b[j])
                dp[i][j] = dp[i + 1][j + 1];
            else
                dp[i][j] = min(1 + dp[i + 1][j], min(1 + dp[i][j + 1], 1 + dp[i + 1][j + 1]));
        }
    return dp[0][0];
}
void solve(){
    string a, b;
    cin >> a >> b;
    cout << generate_space_optimized(a, b, a.sz, b.sz) << endl;
}
signed main()
{
    ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);
#ifdef LOCAL
    freopen("input.txt", "r", stdin);
#endif
    solve();
}
