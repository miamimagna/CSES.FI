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
bool isPossible(v<int>& a, int k, int val){
    int sum = 0, cnt = 1;
    for(auto x: a){
        sum += x;
        if(cnt > k || sum > val)
            sum = x, cnt += 1;
    }
    return cnt <= k;
}
void solve()
{
    int n, k; 
    cin >> n >> k;
    v<int> a(n);
    int lo = -1e9, hi = 0, ans = -1;
    for(auto &x: a) 
        cin >> x, hi += x, lo = max(lo, x);
    while(lo <= hi){
        int mid = (lo + hi) >> 1;
        if(isPossible(a, k, mid)) ans = mid, hi = mid - 1;
        else lo = mid + 1;
    }
    cout << ans << endl;
}
signed main()
{
    solve();
}
