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
#define pb push_back 
void solve()
{
    int n, hi, lo;
    cin >> n >> lo >> hi;
    v<int> a(n);
    for(auto &x: a) 
        cin >> x;
    v<int> prefix{0};
    for(auto x: a) 
        prefix.pb(prefix.back() + x);
    multiset<int> s;
    int ans = -1e18;
    for(int i = lo; i <= n; i++){
        s.insert(prefix[i - lo]);
        int sum = prefix[i] - *s.begin();
        ans = max(ans, sum);
        if(i >= hi) s.erase(s.find(prefix[i - hi]));
    }
    cout << ans << endl;
}
signed main()
{
    solve();
}
