#include <cstdio>
#include <iostream>
#include <vector>
#include <string>
using namespace std;
// preprocessing to make code easier
template <typename T>
using v = vector<T>;
#define int long long
int mod = 1e9 + 7;
void solve(){
    int n = 1e6;
    v<int> dp_double(n + 1), dp_single(n + 1);
    dp_double[1] = dp_single[1] = 1;
    for(int i = 2; i <= n; i++)
        dp_double[i] = (dp_double[i - 1] * 2 + dp_single[i - 1]) % mod,
        dp_single[i] = (dp_double[i - 1] + dp_single[i - 1] * 4) % mod;

    int t; cin >> t;
    while(t--){
        int n; cin >> n;
        cout << (dp_double[n] + dp_single[n]) % mod << endl;
    }
}
signed main()
{
    solve();
}
