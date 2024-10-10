#include <cstdio>
#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <utility>
#include <set>
#include <unordered_map>
#define int long long
using namespace std;
// preprocessing to make code easier
template <typename T>
using v = vector<T>;
#define ff first
#define ss second
#define sortv(a) sort(a.begin(), a.end())
void solve()
{
    int n, target, __cnt = 0;
    cin >> n >> target;
    v<pair<int, int>> a(n);
    for(auto &[x, y]: a)
        y = ++__cnt, cin >> x;
    sortv(a);
  // map will store all sums of pair of values that are already visited
    unordered_map<int, pair<int, int>> mp;
    mp[a[0].ff + a[1].ff] = {a[0].ss, a[1].ss};
    for(int i = 2; i < n; i++){
        for(int j = i + 1; j < n; j++){
          // now search for all remaining pair of values in so that target - sum is present in map(can be done in n^2)
            int sum = a[i].ff + a[j].ff;
            if(mp.count(target - sum)){
                auto [first, second] = mp[target - sum];
                // if found print index
                cout << first << ' ' << second << ' ' << a[i].ss << ' ' << a[j].ss << endl;
                return;
            }
        }
        // update map after visiting a new value
        for(int j = 0; j < i; j++)
            mp[a[i].ff + a[j].ff] = {a[i].ss, a[j].ss};
    }
    cout << "IMPOSSIBLE" << endl;
}
signed main()
{
#ifdef LOCAL
    freopen("input.txt", "r", stdin);
#endif
    solve();
}
