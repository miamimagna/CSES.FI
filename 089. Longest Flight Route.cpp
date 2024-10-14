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
#define pb push_back 
#define eb emplace_back 
#define int long long
int mod = 1e9 + 7;
void solve(){
    int n, m;
    cin >> n >> m;
    v<v<int>> adj(n + 1);
    v<int> indeg(n + 1);
    while(m--){
        int a, b;
        cin >> a >> b;
        adj[a].pb(b);
        indeg[b]++;
    }
    v<int> level(n + 1), parent(n + 1);
    queue<int> q;
    for(int i = 2; i <= n; i++)
        if(!indeg[i]) q.push(i);
    while(q.sz){
        int x = q.front(); q.pop();
        for(int next: adj[x])
            if(next != 1 && !--indeg[next]) q.push(next);
    }
    q.push(1);
    while(q.sz){
        int x = q.front(); q.pop();
        for(int next: adj[x]){
            if(level[next] < level[x] + 1)
                level[next] = level[x] + 1,
                parent[next] = x;
            parent[next] = x;
            if(!(--indeg[next]))
                q.push(next);
        }
    }
    if(!parent[n]) cout << "IMPOSSIBLE" << endl;
    else {
        v<int> ans;
        for(int cur = n; cur; cur = parent[cur])
            ans.pb(cur);
        reverse(ans.begin(), ans.end());
        cout << ans.sz << endl;
        for(auto x: ans) cout << x << ' '; cout << endl;
    }
}
signed main()
{
    solve();
}
