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
int generate(int a, int b, v<v<int>>& dp){
    if(a == b) return 0;
    else if(dp[a][b] != -1) return dp[a][b];
    dp[a][b] = 1e9;
    for(int i = 1, x, y; i <= min(a - 1, b); i++)
        x = generate(a - i, b, dp),
        y = generate(i, b, dp),
        dp[a][b] = min(dp[a][b], 1 + x + y);
    for(int i = 1, x, y; i <= min(a, b - 1); i++)
        x = generate(a, b - i, dp),
        y = generate(a, i, dp),
        dp[a][b] = min(dp[a][b], 1 + x + y);
    return dp[a][b];
}
void solve(){
    int a, b;
    cin >> a >> b;
    v<v<int>> dp(a + 1, v<int>(b + 1, -1));
    cout << generate(a, b, dp) << endl;
}
signed main()
{
    solve();
}
