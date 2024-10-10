#include <cstdio>
#include <iostream>
#include <vector>
#include <utility>
#include <algorithm>
using namespace std;
// preprocessing to make code easier 
template <typename T> 
using v = vector<T>; 
#define int long long
int mod = 1e9 + 7;
void solve(){
    int m, n, q;
    cin >> n >> m >> q;
    v<v<int>> dist(n + 1, v<int>(n + 1, 1e18));
    while(m--){
        int from, to, cost;
        cin >> from >> to >> cost;
        dist[from][to] = min(cost, dist[from][to]);
        dist[to][from] = min(cost, dist[from][to]);
    }
    for(int i = 0; i <= n; i++)
        dist[i][i] = 0;
    for(int i = 1; i <= n; i++)
        for(int j = 1; j <= n; j++)
            for(int k = 1; k <= n; k++){
                dist[j][k] = min(dist[j][k], dist[j][i] + dist[i][k]);
            }

    while(q--){
        int x, y;
        cin >> x >> y;
        if(dist[x][y] == 1e18) dist[x][y] = -1;
        cout << dist[x][y] << endl;
    }
}
signed main()
{
    solve();
}
