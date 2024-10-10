#include <cstdio>
#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <numeric>
using namespace std;
// preprocessing to make code easier
template <typename T>
using v = vector<T>;
#define sz size()
#define int long long
int mod = 1e9 + 7;
void solve(){
    int n, sum = 0;
    cin >> n;
    v<int> a(n);
    for(auto &x: a) 
        cin >> x, sum += x;
    sort(a.begin(), a.end());
    v<bool> dp(sum + 1), prev(sum + 1);
    prev[0] = dp[0] = 1;
    for(int i = 0; i < n; i++, prev = dp){
        for(int cur = 0; cur < sum; cur++)
            if(prev[cur])
                dp[cur + a[i]] = 1;
    }
    int total = accumulate(dp.begin(), dp.end(), 0ll) - 1;
    cout << total << endl;
    for(int i = 1; i <= sum; i++)
        if(dp[i]) cout << i << ' ';
    cout << endl;
}
signed main()
{
    solve();
}
