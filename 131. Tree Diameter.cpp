#include <iostream>
#include <vector>
#include <cstdio>
#include <algorithm>
using namespace std;
using Graph = vector<vector<int>>;
Graph adj;
vector<int> vis;
int ans = 0;
int dfs(int i)
{
    vis[i] = 1;
    int mx = -1, smx = -1;
    for (int child : adj[i])
    {
        if (vis[child])
            continue;
        int depth = dfs(child);
        if (depth > mx)
            smx = mx, mx = depth;
        else if (depth > smx)
            smx = depth;
    }
    if (ans < mx + smx + 2)
        ans = mx + smx + 2;
    return mx + 1;
}
int main()
{
    int n;
    cin >> n;
    adj.resize(n + 1);
    vis.resize(n + 1);
    for (int i = 0; i < n - 1; i++)
    {
        int x, y;
        cin >> x >> y;
        adj[x].push_back(y);
        adj[y].push_back(x);
    }
    dfs(1);
    cout << ans << endl;
}
