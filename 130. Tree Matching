#include <iostream>
#include <vector>
#include <cstdio>
#include <algorithm>
using namespace std;
using Graph = vector<vector<int>>;
Graph adj;
vector<int> vis;
pair<int, int> dfs(int i)
{
    int inc = 0, exc = 0, mx = -1e9;
    vis[i] = 1;
    for (int child : adj[i])
    {
        if (vis[child])
            continue;
        auto [cinn, cexx] = dfs(child);
        exc += max(cinn, cexx);
        if (cexx - cinn > mx)
            mx = cexx - cinn;
    }
    inc = exc;
    if (mx >= 0)
        inc++;
    return {inc, exc};
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
    auto [x, y] = dfs(1);
    cout << x << endl;
}
