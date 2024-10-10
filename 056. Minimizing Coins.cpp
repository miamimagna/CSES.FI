#include <cstdio>
#include <iostream>
#include <vector>
#include <algorithm>
#include <utility>
#include <set>
#define int long long
using namespace std;
// preprocessing to make code easier 
template <typename T> 
using v = vector<T>; 
// memoization
int generate(int target, v<int>& coins, v<int>& dp){
    if(target == 0) return 0;
    if(dp[target] != 1e9)
        return dp[target];
    for(int x: coins)
        if(target - x >= 0)
            dp[target] = min(dp[target], 1 + generate(target - x, coins, dp));
    return dp[target];
}
// tabulation
int generate_tabulation(int target, v<int>& coins, v<int>& dp){
    dp[0] = 0;
    for(int i = 1; i <= target; i++)
        for(auto x: coins)
            if(i - x >= 0)
                dp[i] = min(dp[i], 1 + dp[i - x]);
    return dp[target];
}
void solve()
{
    int n, target;
    cin >> n >> target;
    v<int> a(n);
    for(auto &x: a)
        cin >> x;
    v<int> dp(target + 1, 1e9);
    int ans = generate_tabulation(target, a, dp);
    cout << (ans == 1e9? -1: ans) << endl;
}
signed main()
{
    solve();
}
