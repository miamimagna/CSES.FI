#include <cstdio>
#include <iostream>
#include <vector>
#include <utility>
#include <algorithm>
#include <unordered_set>
using namespace std;
// preprocessing to make code easier 
template <typename T> 
using v = vector<T>; 
#define pb push_back 
#define eb emplace_back 
#define int long long
void solve(){
    int n, m;
    cin >> n >> m;
    v<v<pair<int, int>>> adj(n + 1);
    v<tuple<int, int, int>> edges(m);
    for(auto &[from, to, cost]: edges)
        cin >> from >> to >> cost,
        adj[from].eb(to, cost);
    v<int> dist(n + 1);
    for(int i = 0; i < max(n - 1, 1ll); i++)
        for(auto [from, to, cost]: edges)
            dist[to] = min(dist[to], dist[from] + cost);
    bool ans = false;
    v<int> parent(n + 1, -1);
    // run bellman again but this time check distances and trace parent as well
    for(int i = 0; i < max(n - 1, 1ll); i++)
        for(auto[from, to, cost]: edges)
            if(dist[to] > dist[from] + cost)
                dist[to] = dist[from] + cost,
                parent[to] = from,
                ans = true;
    if(ans){
        int root = 0;
        for(int i = 1; i <= n; i++)
            if(parent[i] != -1){
                root = i;
                break;
            }
        v<int> cycle{root};
        unordered_set<int> s;
        while(!s.count(root)){
            s.insert(root);
            root = parent[root];
            cycle.pb(root);
        }
        cout << "YES" << endl;
        reverse(cycle.begin(), cycle.end());
        unordered_set<int> start;
        int i = -1;
        do{
            if(i >= 0) start.insert(cycle[i]);
            i++;
            cout << cycle[i] << ' '; 
        }while(!start.count(cycle[i]));
        cout << endl;
    }
    else cout << "NO" << endl;
}
signed main()
{
    solve();
}
