#include <cstdio>
#include <iostream>
#include <vector>
#include <string>
#include <utility>
#include <algorithm>
using namespace std;
// preprocessing to make code easier
template <typename T>
using v = vector<T>;
#define sz size()
#define int long long
int mod = 1e9 + 7;
int n, m;
void dfs(int i, int j, v<string> &a){
    if(i == n || i == -1 || j == -1 || j == m || a[i][j] == '#') return;
    a[i][j] = '#';
    dfs(i + 1, j, a);
    dfs(i, j + 1, a);
    dfs(i - 1, j, a);
    dfs(i, j - 1, a);
}
void solve(){
    cin >> n >> m;
    v<string> a(n);
    for(auto &x: a) cin >> x;
    int ans = 0;
    for(int i = 0; i < n; i++)
        for(int j = 0; j < m; j++)
            if(a[i][j] == '.')
                ans++, 
                dfs(i, j, a);
    cout << ans << endl;
}
signed main()
{
#ifdef LOCAL
    freopen("input.txt", "r", stdin);
#endif
    solve();
}
