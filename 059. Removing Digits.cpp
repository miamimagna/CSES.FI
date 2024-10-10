#include <cstdio>
#include <iostream>
#include <vector>
#include <string>
using namespace std;
// preprocessing to make code easier
template <typename T>
using v = vector<T>;
int mod = 1e9 + 7;
int generate(int n, v<int>& dp){
    if(n == 0) return 0;
    if(dp[n] != 1e9) return dp[n];
    string s = to_string(n);
    for(char ch: s){
        int x = ch - '0';
        dp[n] = min(dp[n], 1 + generate(n - x, dp));
    }
    return dp[n];
}
int generate_tabulation(int n, v<int> dp = v<int>(1e6 + 1, 1e9)){
    for(int i = !(dp[0] = 0); i <= n; i++)
        for(char ch: to_string(i))
            dp[i] = min(dp[i], 1 + dp[i - ch + '0']);
    return dp[n];
}
void solve()
{
    int n; 
    cin >> n;
    cout << generate_tabulation(n) << endl;
}
int main()
{
#ifdef LOCAL
    freopen("input.txt", "r", stdin);
#endif
    solve();
}
