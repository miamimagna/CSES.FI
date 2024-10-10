#include <cstdio>
#include <iostream>
#include <vector>
#include <string>
#include <utility>
#include <queue>
#include <algorithm>
using namespace std;
// preprocessing to make code easier
template <typename T>
using v = vector<T>;
#define sz size()
#define int long long
int mod = 1e9 + 7;
bool possible = false, conti = true;
v<int> ans;
void dfs(int i, v<v<int>>& adj, v<int> &depth){
    for(int x: adj[i]){
        if(possible) break;
        if(depth[x] == -1) 
            depth[x] = depth[i] + 1,
            dfs(x, adj, depth);
        else if(depth[i] - depth[x] >= 2){
            possible = 1;
            ans.push_back(x);
            break;
        }
    }
    if(possible && conti) ans.push_back(i), conti = ans.back() != ans.front();
}
void solve(){
    int n, m; 
    cin >> n >> m;
    v<v<int>> adj(n + 1);
    while(m--){
        int x, y;
        cin >> x >> y;
        adj[x].push_back(y), adj[y].push_back(x);
    }
    v<int> depth(n + 1, -1);
    for(int i = 0; i < n; i++)
        if(depth[i] == -1)
            depth[i] = 0, 
            dfs(i, adj, depth);
    if(ans.sz){
        cout << ans.sz << endl;
        for(auto x: ans) cout << x << ' '; 
        cout << endl;
    }
    else cout << "IMPOSSIBLE" << endl;
}
signed main()
{
#ifdef LOCAL
    freopen("input.txt", "r", stdin);
#endif
    solve();
}
