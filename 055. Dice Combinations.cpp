#include <iostream>
#include <vector>
#include <utility>
#define int long long
using namespace std;
// preprocessing to make code easier 
template <typename T> 
using v = vector<T>; 
int mod = 1e9 + 7;
// memoisation
int generate(int n, v<int> & moves, v<int> &dp){
    if(n == 0) return 1;
    if(dp[n] != -1) return dp[n];
    dp[n] = 0;
    for(auto x: moves)
        if(n - x >= 0)
            dp[n] = (dp[n] + generate(n - x, moves, dp)) % mod;
    return dp[n];
}
// tabulation
int generate_tabulation(int n, v<int>& moves, v<int>& dp){
    dp[0] = 1;
    for(int i = 1; i <= n; i++){
        dp[i] = 0;
        for(auto x: moves)
            if(i - x >= 0)
                dp[i] = (dp[i] + dp[i - x]) % mod;
    }
    return dp[n];
}
void solve()
{
    int n;
    cin >> n;
    v<int> moves{1, 2, 3, 4, 5, 6};
    v<int> dp(n + 1, -1);
    cout <<  generate(n, moves, dp) << endl;
}
signed main()
{
    solve();
}
