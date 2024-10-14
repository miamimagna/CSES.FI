#include <cstdio>
#include <iostream>
#include <vector>
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
#define eb emplace_back 
#define int long long
int mod = 1e9 + 7;
void solve(){
    int m, n;
    cin >> n >> m;
    v<v<pair<int, int>>> adj(n + 1);
    while(m--){
        int from, to, cost;
        cin >> from >> to >> cost;
        adj[from].eb(to, cost);
    }
    // (distance, node, haveUsed) will be our tuple where haveUsed will signify that one move
    minheap<tuple<int, int, bool>> q;
    // dist [0] is raw distance, dist[1] is utilized distance
    v<v<int>> dist(2, v<int>(n + 1, 1e17));
    dist[0][1] = 0;
    #define push emplace
    q.push(0, 1, 0);
  // dijkstra magic starts from here
    while(q.sz){
        auto [distance, node, haveUsed] = q.top(); q.pop();
        if(dist[haveUsed][node] != distance) continue;
        for(auto [next, cost]: adj[node]){
            // utilize move if available
            if(!haveUsed){
                if(dist[1][next] > dist[0][node] + cost/2)
                    dist[1][next] = dist[0][node] + cost/2,
                    q.push(dist[1][next], next, 1);
            }
            // the default dijkstra move
            if(dist[haveUsed][next] > dist[haveUsed][node] + cost)
                dist[haveUsed][next] = dist[haveUsed][node] + cost,
                q.push(dist[haveUsed][next], next, haveUsed);
        }
    }
    cout << min(dist[0].back(), dist[1].back()) << endl;
    #undef push
}
signed main()
{
    solve();
}
