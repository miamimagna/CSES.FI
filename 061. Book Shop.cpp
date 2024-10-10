#include <cstdio>
#include <iostream>
#include <vector>
#include <string>
using namespace std;
// preprocessing to make code easier
template <typename T>
using v = vector<T>;
int mod = 1e9 + 7;
// it's getting repetitive so no tabulation and memo this time around
void solve(){
    int n, max_price;
    cin >> n >> max_price;
    v<int> prices(n), pages(n);
    for(auto &x: prices) cin >> x;
    for(auto &x: pages) cin >> x;

    v<int> dp(max_price + 1), prev=dp;
    for(int j = 0; j < n; j++, prev = dp)
        for(int i = 1; i <= max_price; i++)
            if(i >= prices[j])
                dp[i] = max(dp[i], pages[j] + prev[i - prices[j]]);
    cout << dp.back() << endl;
}
int main()
{
    solve();
}
