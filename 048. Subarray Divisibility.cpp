#include <cstdio>
#include <iostream>
#include <vector>
#include <algorithm>
#include <utility>
#include <unordered_map>
#define int long long
using namespace std;
// preprocessing to make code easier 
template <typename T> 
using v = vector<T>; 
#define pb push_back 
void solve()
{
    int n, ans = 0; 
    cin >> n ;
    v<int> a(n);
    for(auto &x: a) 
        cin >> x;
    v<int> prefix{0};
    for(int x: a)
        prefix.pb(prefix.back() + x);
    unordered_map<int, int> mp(210000);
    for(int x: prefix){
        if(x % n < 0)
            x = n + x % n;
        if(mp.count(x % n))
            ans += mp[x % n];
        mp[x % n]++;
    }
    cout << ans << endl;
}
signed main()
{
    solve();
}
