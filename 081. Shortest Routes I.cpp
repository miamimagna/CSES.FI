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
template<typename t>
using minheap = priority_queue<t, v<t>, greater<t>>;
#define sz size() 
#define pb push_back 
#define eb emplace_back 
#define int long long
int mod = 1e9 + 7;
void dijkstra(int src, v<v<pair<int, int>>> &adj, v<int>& dist) {
    minheap<pair<int, int>> q;
    #define push emplace
    q.push(0, src);
    dist[src] = 0;
    while(q.sz){
        auto [cost, node] = q.top(); q.pop();
        if(cost != dist[node]) continue;
        for(auto [next, nxtcost]: adj[node])
            if(cost + nxtcost < dist[next])
                dist[next] = cost + nxtcost, q.push(dist[next], next);
    }
    #undef push
}
void solve(){
    int m, n;
    cin >> n >> m;
    v<v<pair<int, int>>> adj(n + 1);
    while(m--){
        int from, to, cost;
        cin >> from >> to >> cost;
        adj[from].eb(to, cost);
    }
    v<int> dist(n + 1, 1e18);
    dijkstra(1, adj, dist);
    for(int i = 1; i <= n; i++)
        cout << dist[i] << ' '; 
    cout << endl;
}
signed main()
{
#ifdef LOCAL
    freopen("input.txt", "r", stdin);
#endif
    solve();
}
