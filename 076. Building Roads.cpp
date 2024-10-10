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
class DSU{
    v<int> parent, size;
    public:
    DSU(int n): parent(n), size(n, 1){
        for(int i = 0; i < n; i++)
            parent[i] = i;
    }
    int find(int u){
        return parent[u] == u? u: parent[u] = find(parent[u]);
    }
    void unions(int u, int v){
        u = find(u), v = find(v);
        if(u != v){
            if(size[u] < size[v]) swap(u, v);
            parent[v] = u;
            size[u] += size[v];
        }
    }
};
int n, m;
void solve(){
    int n, m;
    cin >> n >> m;
    DSU dsu(n + 1);
    v<v<int>> adj(n + 1);
    while(m --){
        int x, y;
        cin >> x >> y;
        adj[x].push_back(y), adj[y].push_back(x);
        dsu.unions(x, y);
    }
    v<pair<int, int>> ans;
    for(int i = 2; i <= n; i++)
        if(dsu.find(i) != dsu.find(i - 1)) ans.emplace_back(i - 1, i), dsu.unions(i, i - 1);
    cout << ans.sz << endl;
    for(auto [x,y]: ans) cout << x << ' ' << y << endl;
}
signed main()
{
#ifdef LOCAL
    freopen("input.txt", "r", stdin);
#endif
    solve();
}
