#include <cstdio>
#include <iostream>
#include <vector>
#include <utility>
#include <algorithm>
using namespace std;
// preprocessing to make code easier 
template <typename T> 
using v = vector<T>; 
#define eb emplace_back
#define int long long
int mod = 1e9 + 7;
void dfs_reverse(int x, v<bool> &vis, v<bool> &faults, v<v<pair<int, int>>> &adj_reverse)
{
    // if we get any fault, we mark end of fault as true
    if(faults[x]) faults.back() = 1;
    // if fault has been found or visited already
    if(vis[x] || faults.back()) return;
    // mark visited and traverse all child in reverse
    vis[x] = 1;
    for(auto [next, cost]: adj_reverse[x]){
        dfs_reverse(next, vis, faults, adj_reverse);
    }
}
void solve(){
    int n, m;
    cin >> n >> m;
    v<tuple<int, int, int>> edge;
    while(m--){
        int a, b, x;
        cin >> a >> b >> x;
        edge.eb(a, b, x);
    }
    v<int> dist(n + 1, -1e17);
    dist[1] = 0;
    // apply bellman ford n - 1 times
    for(int i = 0; i < n - 1; i++)
        for(auto [from, to, cost]: edge)
            if(dist[to] < dist[from] + cost && dist[from] != -1e17)
                dist[to] = dist[from] + cost;
    // vis is visited array for dfs
    // faults is array that will store cyclic element with positive sum
    v<bool> vis(n + 1), faults(vis);
    for (auto [from, to, cost] : edge)
        if (dist[to] < dist[from] + cost && dist[from] != -1e17)
            faults[to] = 1;
    // we will make reverse adjacency list and traverse it in reverse from nth node
    v<v<pair<int, int>>> adj_reverse(n + 1);
    for(auto [from, to, cost]: edge)
        adj_reverse[to].eb(from, cost);
    dfs_reverse(n, vis, faults, adj_reverse);
    if(!faults.back()) cout << dist.back() << endl;
    else cout << -1 << endl;
}
signed main()
{
#ifdef LOCAL
    freopen("input.txt", "r", stdin);
#endif
    solve();
}
