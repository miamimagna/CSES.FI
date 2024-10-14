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
    queue<int> q;
    for(int i = 2; i <= n; i++)
        if(!indeg[i]) q.push(i);
    while(q.sz){
        int x = q.front(); q.pop();
        for(int next: adj[x])
            if(next != 1 && !--indeg[next]) q.push(next);
    }
    q.push(1);
    v<int> reach(n + 1);
    reach[1] = 1;
    while(q.sz){
        int x = q.front(); q.pop();
        for(int next: adj[x]){
            reach[next] = (reach[next] + reach[x]) % mod;
            if(!--indeg[next]) q.push(next);
        }
    }
    cout << reach.back() << endl;
}
signed main()
{
    solve();
}
