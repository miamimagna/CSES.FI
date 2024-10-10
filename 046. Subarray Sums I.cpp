#include <cstdio>
#include <iostream>
#include <vector>
#include <algorithm>
#include <utility>
#include <stack>
#define int long long
using namespace std;
// preprocessing to make code easier 
template <typename T> 
using v = vector<T>; 
void solve()
{
    int n, target;
    cin >> n >> target;
    v<int> a(n);
    for(auto &x: a)
        cin >> x;
    int l = 0, cnt = 0, sum = 0;
    for(int r = 0; r < n; r++){
        sum += a[r];
        while(sum > target)
            sum -= a[l++];
        if(sum == target) cnt++;
    }
    cout << cnt << endl;
}
signed main()
{
#ifdef LOCAL
    freopen("input.txt", "r", stdin);
#endif
    solve();
}
