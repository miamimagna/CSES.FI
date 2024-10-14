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
/*
another solution to this problem is using graph coloring algorithm, to ensure you have cycle with two or more node, we can check following condition:
parent[cycleend] should not be cyclestart
int cyclestart = -1, cycleend = -1;
bool dfs(int node, v<v<int>>& adj, v<int>& color, v<int>& parent){
    color[node] = 1;
    for(int next: adj[node]){
        if(!color[next]){
            parent[next] = node;
            if(dfs(next, adj, color, parent))
                return true;
        }
        if(color[next] == 1 && parent[node] != next){
            parent[next] = -1;
            cyclestart = node;
            cycleend = next;
            return true;
        }
    }
    color[node] = 2;
    return false;
}
void solve(){
    int n, m;
    cin >> n >> m;
    v<v<int>> adj(n + 1);
    while(m--){
        int a, b;
        cin >> a >> b;
        adj[a].pb(b);
        adj[b].pb(a);
    }
    v<int> color(n + 1), parent(n + 1, -1);
    bool found = 0;
    for(int i = 1; i <= n; i++)
        if(!color[i] && dfs(i, adj, color, parent)){
            found = 1;
            break;
        }
    if(found){
        int cur = cyclestart;
        v<int> ans{cur};
        while(cur != cycleend){
            cur = parent[cur];
            ans.push_back(cur);
        }
        ans.push_back(ans.front());
        reverse(ans.begin(), ans.end());
        cout << ans.sz << endl;
        for(auto x: ans) cout << x << ' '; 
        cout << endl;
    }
    else cout << "IMPOSSIBLE" << endl;
}
*/
// here possible denotes existence of solution and conti will tell us when to stop adding nodes to answer
bool possible = false, conti = true;
v<int> ans;
// in most simple terms we need to detect a cycle of 3 or more nodes, we can do that using a depth array that will store the depth at which a node was found
// finally when something is encountered again, we will check if it's depth is more than 2, if yes we will backtrach answer
void dfs(int i, v<v<int>>& adj, v<int> &depth){
    for(int x: adj[i]){
        if(possible) break;
        if(depth[x] == -1) 
            depth[x] = depth[i] + 1,
            dfs(x, adj, depth);
        else if(depth[i] - depth[x] >= 2){
            possible = 1;
            ans.push_back(x);
            break;
        }
    }
    if(possible && conti) ans.push_back(i), conti = ans.back() != ans.front();
}
void solve(){
    int n, m; 
    cin >> n >> m;
    v<v<int>> adj(n + 1);
    while(m--){
        int x, y;
        cin >> x >> y;
        adj[x].push_back(y), adj[y].push_back(x);
    }
    v<int> depth(n + 1, -1);
    for(int i = 0; i < n; i++)
        if(depth[i] == -1)
            depth[i] = 0, 
            dfs(i, adj, depth);
    if(ans.sz){
        cout << ans.sz << endl;
        for(auto x: ans) cout << x << ' '; 
        cout << endl;
    }
    else cout << "IMPOSSIBLE" << endl;
}
signed main()
{
#ifdef LOCAL
    freopen("input.txt", "r", stdin);
#endif
    solve();
}
