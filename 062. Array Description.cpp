#include <cstdio>
#include <iostream>
#include <vector>
#include <string>
using namespace std;
// preprocessing to make code easier
template <typename T>
using v = vector<T>;
int mod = 1e9 + 7;
void solve(){
    int n, m;
    cin >> n >> m;
    v<int> a(n);
    for(auto &x: a) 
        cin >> x;
    v<int> dp, prev(m + 1);
    if(a.back()) prev[a.back()] = 1;
    else prev.assign(m + 1, 1); 
    prev[0] = 0;
    dp = prev;
    for(int i = n - 2; i >= 0; i--, prev = dp){
        // if a[i] != 0 then we just need to add a[i] - 1, a[i] and a[i] + 1
        if(a[i]){
            for(auto &x: dp) x = 0;
            dp[a[i]] = prev[a[i]];
            if(a[i] != m) dp[a[i]] = (dp[a[i]] + prev[a[i] + 1]) % mod;
            if(a[i] != 1) dp[a[i]] = (dp[a[i]] + prev[a[i] - 1]) % mod;
        }
        // otherwise we need to add same thing as above but for every possible answer
        else for(int j = 1; j <= m; j++){
            if(j != m) dp[j] = (dp[j] + prev[j + 1]) % mod;
            if(j != 1) dp[j] = (dp[j] + prev[j - 1]) % mod;
        }
    }
    int sum = 0;
    for(auto x: prev)
        sum = (sum + x) % mod;
    cout << sum << endl;
}
int main()
{
    solve();
}
