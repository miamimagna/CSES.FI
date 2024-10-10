#include <cstdio>
const int N = 1e6 + 1;
int dp[N] = {};
int coins[100] = {};
int mod = 1e9 + 7;
#include <vector>
// this is memoisation just for reference
int generate_memo(int target, v<int>& coins, v<int>& dp){
    if(target == 0) return 1;
    if(dp[target] != -1) return dp[target];
    dp[target] = 0;
    for(auto x: coins)
        if(target - x >= 0)
            dp[target] = (dp[target] + generate_memo(target - x, coins, dp)) % mod;
    return dp[target];
}
void solve(){
    int n, target;
    scanf("%d", &n);
    scanf("%d", &target);
    for(int i = 0; i < n; i++)
        scanf("%d", &coins[i]);
    dp[0] = 1;
    for(int i = 0; i < target; i++)
        if(dp[i] != 0)
            for(int j = 0; j < n; j++)
                if(i + coins[j] <= target)
                    dp[i + coins[j]] = (dp[i + coins[j]] + dp[i]) % mod;
    printf("%d\n", dp[target]);
}
signed main(){
    solve();
}
