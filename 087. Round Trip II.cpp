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
#define sz size() 
#define pb push_back 
#define eb emplace_back 
#define int long long
int mod = 1e9 + 7;
// cur will contain current dfs nodes and ans will contain answer
v<int> cur, ans;
// dfs on reverse of adjacency list
void dfs_reverse(int node, v<v<int>>& adj, v<bool> &vis){
  // if answer has been found stop
    if(ans.sz) return;
    cur.pb(node);
  // answer will be found at first loop
    if(vis[node]){
        ans = cur;
        return;
    }
  // finally make visited = 1 and traverse graph
    vis[node] = 1;
    for(int next: adj[node])
        dfs_reverse(next, adj, vis);
  // make vis = 0 for backtrack
    vis[node] = 0;
    cur.pop_back();
}
void solve(){
    int n, m;
    cin >> n >> m;
    v<v<int>> adj(n + 1), adjrev{adj};
  // indegree of each node for kahn's algorithm
    v<int> indeg(n + 1);
  // maintain 2 different adjacency list, one forward and one reversed
    while(m--){
        int a, b;
        cin >> a >> b;
        adj[a].pb(b);
        adjrev[b].pb(a);
        indeg[b]++;
    }
    queue<int> q;
  // khan's algorithm
    for(int i = 1; i <= n; i++)
        if(!indeg[i])
            q.push(i);
    while(q.sz){
        int node = q.front(); q.pop();
        for(int next: adj[node]){
            indeg[next]--;
            if(!indeg[next])
                q.push(next);
        }
    }
  // solution creation from khan's algorithm will be based on finding node with nonzero indegree and 
  // performing reverse traversal
    int root = 0;
    for(int i = 1; i <= n; i++)
        if(indeg[i])
            root = i;
  // if node was found, there is a cycle
    if(root){
        v<bool> vis(n + 1);
        dfs_reverse(root, adjrev, vis);
        vis.assign(n + 1, 0);
      // answer will be found in reverse format(it will contain some non cyclic node which we will filter uisng visited array once again)
        reverse(ans.begin(), ans.end());
        v<int> res;
        for(int i = 0; i < ans.sz; i++){
            res.pb(ans[i]);
            if(vis[ans[i]]) break;
            vis[ans[i]] = 1;
        }
        cout << res.sz << endl;
        for(int x: res) cout << x << ' ';
        cout << endl;
    }
    else cout << "IMPOSSIBLE" << endl;
}
signed main()
{
    solve();
}
