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
template<typename t>
using minheap = priority_queue<t, v<t>, greater<t>>;
#define sz size() 
#define pb push_back 
#define eb emplace_back 
#define int long long
int mod = 1e9 + 7;
void solve(){
    int n, m;
    cin >> n >> m;
    v<v<pair<int, int>>> adj(n + 1);
    v<int> indeg(n + 1);
    while(m--){
        int a, b, c;
        cin >> a >> b >> c;
        adj[a].eb(b, c);
    }
    // dijkstra begins
    v<int> dist(n + 1, 1e17);
    minheap<pair<int, int>> pq;
    #define push emplace
    pq.push(0, 1);
    dist[1] = 0;
    while(pq.sz){
        auto [distance, node] = pq.top(); pq.pop();
        if(distance != dist[node]) continue;
        for(auto [next, cost]: adj[node])
            if(dist[next] > distance + cost)
                dist[next] = distance + cost,
                pq.push(dist[next], next);
    }
    int min_distance = dist.back();
    #undef push
    // create new adjacency list with just smallest edges
    v<v<pair<int, int>>> adj2(n + 1);
    for(int i = 1; i <= n; i++)
        for(auto [next, cost]: adj[i])
            if(dist[next] == dist[i] + cost)
                adj2[i].eb(next, cost),
                indeg[next]++;
    // topological begins
    queue<int> q;
    for(int i = 2; i <= n; i++)
        if(!indeg[i]) q.push(i);
    // here we need 3 things to devise, number of ways, minimum number of nodes, maximum number of nodes
    while(q.sz){
        int x = q.front(); q.pop();
        for(auto [next, cost]: adj2[x])
            if(!--indeg[next]) q.push(next);
    }
    q.push(1);
    v<int> reach(n + 1), mxnodes(n + 1), mnnodes(n + 1, n);
    mnnodes[1] = 0;
    reach[1] = 1;
    while(q.sz){
        int x = q.front(); q.pop();
        for(auto [next, cost]: adj2[x]){
            if(dist[x] + cost == dist[next])
                reach[next] = (reach[next] + reach[x]) % mod,
                mxnodes[next] = max(mxnodes[next], mxnodes[x] + 1),
                mnnodes[next] = min(mnnodes[next], mnnodes[x] + 1);
            if(!--indeg[next]) q.push(next);
        }
    }
    cout << min_distance << ' ';
    cout << reach.back() << ' ';
    cout << mnnodes.back() << ' ';
    cout << mxnodes.back() << endl;
}
signed main()
{
    solve();
}
