#include <cstdio>
#include <iostream>
#include <vector>
#include <utility>
#include <queue>
#include <algorithm>
#include <set>
using namespace std;
// preprocessing to make code easier 
template <typename T> 
using v = vector<T>; 
template <typename t>
using maxheap = priority_queue<t>;
template<typename t>
using minheap = priority_queue<t, v<t>, greater<t>>;
#define heap(T, comp) priority_queue<T, v<T>, comp> 
#define sz size() 
#define pb push_back 
#define eb emplace_back 
#define int long long
int mod = 1e9 + 7;
/*
this is kruskal's algorithm solution for the sake of completion
class DSU
{
    v<int> parent, size;

public:
    DSU(int n) : parent(n), size(n, 1)
    {
        for (int i = 0; i < n; i++)
            parent[i] = i;
    }
    int find(int u)
    {
        return parent[u] == u ? u : parent[u] = find(parent[u]);
    }
    void unions(int u, int v)
    {
        u = find(u), v = find(v);
        if (u != v)
        {
            if (size[u] < size[v])
                swap(u, v);
            parent[v] = u;
            size[u] += size[v];
        }
    }
};
void solve(){
    int n, m;
    cin >> n >> m;
    v<tuple<int, int, int>> edges;
    while(m --){
        int from, to, cost;
        cin>>from >> to >> cost;
        edges.eb(cost, from, to);
        edges.eb(cost, to, from);
    }
    sort(edges.begin(), edges.end());
    DSU dsu(n + 1);
    int ans = 0;
    for(auto &[cost, from, to]: edges)
        if(dsu.find(from) != dsu.find(to))
            ans += cost, dsu.unions(from, to);
    bool possible = true;
    for(int i = 2; i <= n; i++)
        if(dsu.find(i) != dsu.find(i - 1))
            possible = false;
    if(possible) cout << ans << endl;
    else cout << "IMPOSSIBLE" << endl;
}
*/
// this is prim's algorithm solution
void solve(){
    int n, m;
    cin >> n >> m;
    v<v<pair<int, int>>> adj(n + 1);
    while(m--){
        int from, to, cost;
        cin >> from >> to >> cost;
        adj[from].eb(to, cost);
        adj[to].eb(from, cost);
    }
    v<bool> vis(n + 1);
    minheap<tuple<int, int, int>> q;
    #define push emplace
    int ans = 0;
    vis[0] = vis[1] = 1;
    for(auto [next, cost]: adj[1])
        q.push(cost, 1, next);
    while(q.sz){
        auto [cost, from, to] = q.top(); q.pop();
        if(vis[to]) continue;
        vis[to] = 1;
        // to get edge we can do edges.eb(from, to, cost)
        ans += cost;
        for(auto [next, cost]: adj[to])
            q.push(cost, to, next);
    }
    #undef push
    int sum = 0;
    for(int x: vis) sum += x;
    if(sum == n + 1)
        cout << ans << endl;
    else cout << "IMPOSSIBLE" << endl;
}
signed main()
{
#ifdef LOCAL
    freopen("input.txt", "r", stdin);
#endif
    solve();
}
