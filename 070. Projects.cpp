#include <cstdio>
#include <iostream>
#include <vector>
#include <map>
#include <utility>
#include <algorithm>
using namespace std;
// preprocessing to make code easier
template <typename T>
using v = vector<T>;
#define int long long
void solve()
{
    map<int, int> mp;
    int n, mx = 0; cin >> n;
    v<tuple<int, int, int>> a(n);
    for(auto &[end, start, reward]: a)
        cin >> start >> end >> reward;
    sort(a.begin(), a.end());
    mp[0] = 0;
    for(auto [end, start, reward]: a){
        int prev_reward = (--mp.lower_bound(start)) -> second;
        mx = max(mx, prev_reward + reward);
        mp[end] = mx;
    }
    cout << mx << endl;
}
signed main()
{
    solve();
}
