#include <cstdio>
#include <iostream>
#include <vector>
using namespace std;
// preprocessing to make code easier 
template <typename T> 
using v = vector<T>; 
int mod = 1e9 + 7;
void solve(){
    int n, target;
    cin >> n >> target;
    v<int> coins(n);
    for(auto &x: coins) 
        cin >> x;
    v<int> dp(target + 1);
 
    dp[0] = 1;
    for (int coin : coins)
        for (int i = coin; i <= target; i++)
            dp[i] = (dp[i] + dp[i - coin]) % mod;
            
    cout << dp.back() << endl;
}
int main(){
    solve();
}
