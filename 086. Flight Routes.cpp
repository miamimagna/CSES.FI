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
template <typename t>
using maxheap = priority_queue<t>;
template<typename t>
using minheap = priority_queue<t, v<t>, greater<t>>;
#define sz size() 
#define pb push_back 
#define eb emplace_back 
#define int long long
int mod = 1e9 + 7;
void solve(){
    int n, m, k;
    cin >> n >> m >> k;
    v<v<pair<int, int>>> adj(n + 1);
    while(m--){
        int from, to, cost;
        cin >> from >> to >> cost;
        adj[from].eb(to, cost);
    }
    minheap<pair<int, int>> q;
    v<maxheap<int>> dist(n + 1);
    dist[1].push(0);
    #define push emplace 
    q.push(0, 1);
    while(q.sz){
        auto [distance, node] = q.top(); q.pop();
        if(distance > dist[node].top()) continue;
        for(auto [next, cost]: adj[node])
        {
            int temp = distance + cost;
            if(dist[next].sz < k)
                dist[next].push(temp),
                q.push(temp, next);
            else if(temp < dist[next].top())
                dist[next].pop(),
                dist[next].push(temp),
                q.push(temp, next);
        }
    }
    v<int> ans;
    while(dist.back().sz) ans.pb(dist.back().top()), dist.back().pop();
    reverse(ans.begin(), ans.end());
    for(auto x: ans) cout << x << ' ';
    cout << endl;
    #undef push
}
signed main()
{
#ifdef LOCAL
    freopen("input.txt", "r", stdin);
#endif
    solve();
}
