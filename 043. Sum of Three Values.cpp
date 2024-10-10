#include <cstdio>
#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <utility>
#include <set>
#include <queue>
#define int long long
using namespace std;
// preprocessing to make code easier
template <typename T>
using v = vector<T>;
#define ff first
#define ss second
#define sortv(a) sort(a.begin(), a.end())
#define each(a) a.begin(), a.end()
void solve()
{
    int n, target, __cnt = 0;
    cin >> n >> target;
    v<pair<int, int>> a(n);
    for(auto &[x, y]: a)
        y = ++__cnt, cin >> x;
    sortv(a);
    for(int i = 0; i < n - 2; i++){
        int hi = n - 1, lo = i + 1, required = target - a[i].ff;
        while(hi > lo){
            int sum = a[hi].ff + a[lo].ff;
            if(sum == required){
                cout << a[i].ss << ' ' << a[lo].ss << ' ' << a[hi].ss << endl;
                return;
            }
            else if(sum > required) hi--;
            else lo++;
        }
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
