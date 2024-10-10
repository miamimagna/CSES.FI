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
#define pb push_back 
void solve()
{
    int n;
    cin >> n;
    v<int> a(n), ans;
    for (auto &x : a)
        cin >> x;
    stack<int> s;
    for(int i = 0; i < n; i++){
        while(s.size() && a[s.top() - 1] >= a[i]) s.pop();
        if(s.empty()) 
            ans.pb(0);
        else ans.pb(s.top());
        s.push(i + 1);
    }
    for(auto x: ans) 
        cout << x << ' '; cout << endl;
}
signed main()
{
#ifdef LOCAL
    freopen("input.txt", "r", stdin);
#endif
    solve();
}
