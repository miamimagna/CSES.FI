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
void solve(){
    int n, m;
    cin >> n >> m;
    v<v<int>> adj(n + 1);
  // indeg array denotes prerequisite for completing a course
    v<int> indeg(n + 1);
    while(m--){
        int a, b;
        cin >> a >> b;
        adj[a].pb(b);
        indeg[b]++;
    }
  // just do topological sorting
    v<int> level(n + 1);
    queue<int> q;
    for(int i = 1; i <= n; i++)
        if(!indeg[i])
            q.push(i), level[i] = 0;
    while(q.sz){
        int x = q.front(); q.pop();
        for(int next: adj[x]){
          // maximize level 
            level[next] = max(level[next], level[x] + 1);
          // only push a course if there are no prerequisite remaining
            if(!(--indeg[next]))
                q.push(next);
        }
    }
  // this line translates to nothing is impossible
    bool impossible = false;
    for(auto x: indeg) impossible = x || impossible;
    if(!impossible){
        int mx = *max_element(level.begin(), level.end());
        v<v<int>> res(mx + 1);
        for(int i = 1; i <= n; i++)
            res[level[i]].pb(i);
        for(auto x: res)
            for(auto y: x) cout << y << ' ';
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
