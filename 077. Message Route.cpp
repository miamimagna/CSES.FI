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
void solve(){
    int n, m;
    cin >> n >> m;
    v<v<int>> adj(n + 1);
    while(m --){
        int x, y;
        cin >> x >> y;
        adj[x].push_back(y), adj[y].push_back(x);
    }
    v<int> dist(n + 1, 1e9);
    dist[1] = 1;
    queue<int> q;
    q.push(1);
    while(q.sz){
        int x = q.front(); q.pop();
        for(auto next: adj[x])
            if(dist[next] > dist[x] + 1){
                dist[next] = dist[x] + 1;
                q.push(next);
            }
    }
    int ans = dist.back();
    if(ans == 1e9) cout << "IMPOSSIBLE" << endl;
    else {
        cout << ans << endl;
        int node = n;
        v<int> path;
        while(ans--)
            for(auto x: adj[node])
                if(dist[x] == dist[node] - 1){
                    path.push_back(node),
                    node = x;
                    break;
                }
        path.push_back(1);
        reverse(path.begin(), path.end());
        for(auto x: path) cout << x << ' '; cout << endl;
    }
}
signed main()
{
#ifdef LOCAL
    freopen("input.txt", "r", stdin);
#endif
    solve();
}
