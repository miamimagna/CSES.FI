#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
template <typename t>
using v = vector<t>;
#define int long long
int bn, gn;
// basically this problem can be converted into max flow problem using a mock source connected to boys and mock sink connected to girls
bool dfs(int node, int target, int threshold, v<v<int>> &adj, v<v<int>> &capacity, v<bool> &vis, v<int> &path)
{
    vis[node] = 1;
    if (node == target)
    {
        path.push_back(node);
        return true;
    }
    for (int i : adj[node])
    {
        if (!vis[i] && capacity[node][i] >= threshold && dfs(i, target, threshold, adj, capacity, vis, path))
        {
            path.push_back(node);
            return true;
        }
    }
    return false;
}
signed main()
{
#ifdef LOCAL
    freopen("input.txt", "r", stdin);
#else
    cin.tie(0)->sync_with_stdio(0);
#endif
    int m;
    cin >> bn >> gn >> m;
    int n = bn + gn + 2;
    // 0 = SRC, girl index = boy_index + gi
    // sink = bn + gn + 1
    v<v<int>> adj(n);
    v<v<int>> capacity(n, v<int>(n));
    // connect boys with src
    for (int i = 1; i <= bn; i++)
        adj[i].push_back(0),
            adj[0].push_back(i),
            capacity[0][i] = 1;
    // connect girls with sink
    for (int j = 1, gi = bn + 1; j <= gn; j++, gi++)
        adj[gi].push_back(n - 1),
            adj[n - 1].push_back(gi),
            capacity[gi][n - 1] = 1;
    int threshold = bn + gn + m;
    while (m--)
    {
        int a, b;
        cin >> a >> b;
        b += bn;
        adj[a].push_back(b);
        adj[b].push_back(a);
        capacity[a][b] = 1;
    }
    int ans = 0;
    v<v<int>> paths;
    while (threshold)
    {
        v<bool> vis(n);
        v<int> path;
        if (!dfs(0, n - 1, threshold, adj, capacity, vis, path))
            threshold >>= 1;
        else
        {
            reverse(path.begin(), path.end());
            paths.push_back(path);
            int pn = path.size();
            int mnw = 1e18;
            for (int i = 0; i < pn - 1; i++)
                mnw = min(mnw, capacity[path[i]][path[i + 1]]);
            for (int i = 0; i < pn - 1; i++)
                capacity[path[i]][path[i + 1]] = 0,
                                           capacity[path[i + 1]][path[i]] = 1;
            ans += mnw;
        }
    }
    cout << paths.size() << endl;
  // now how to print results, simply the pair of boy and girl with negative capacity will be the ones we need to print(those are getting utilized) 
    for (int i = 1; i <= bn; i++)
        for (int j = bn + 1; j <= bn + gn; j++)
            if (capacity[j][i])
                cout << i << ' ' << j - bn << endl;
}
