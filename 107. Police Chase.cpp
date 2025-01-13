#include <cmath>
#include <iostream>
#include <algorithm>
#include <vector>
#include <unordered_map>
#include <cstring>
#include <set>
#include <unordered_set>
using namespace std;
// preprocessing to make code easier
#define int long long
template <typename T>
using v = vector<T>;
int adj[501][501];
int visited[501];
int ans = 0, dest;
bool dfs(int node, int dest, int threshold, v<int> &path)
{
    // cout << node << ' ' << threshold << endl;
    visited[node] = 1;
    if (node == dest)
    {
        path.push_back(node);
        return true;
    }
    for (int i = 1; i <= dest; i++)
    {
        if (visited[i] || adj[node][i] < threshold)
            continue;
        if (dfs(i, dest, threshold, path))
        {
            path.push_back(node);
            return true;
        }
    }
    return false;
}
class DSU
{
    vector<int> parent, size;

public:
    DSU(int n) : parent(n), size(n, 1)
    {
        for (int i = 0; i < n; i++)
            parent[i] = i;
    }
    int find(int u)
    {
        // path compression
        return parent[u] == u ? u : parent[u] = find(parent[u]);
    }
    void unions(int u, int v)
    {
        // union by size
        u = find(u), v = find(v);
        if (u == v)
            return;
        if (size[u] < size[v])
            swap(u, v);
        parent[v] = u;
        size[u] += size[v];
    }
};
DSU source(1);
void dfs2(int node, v<bool> &vis)
{
    vis[node] = 1;
    for (int i = 1; i <= dest; i++)
        if (!vis[i] && adj[node][i] > 0)
            source.unions(i, node), dfs2(i, vis);
}
signed main()
{
#ifdef LOCAL
    freopen("input.txt", "r", stdin);
    // freopen("output.txt", "w", stdout);
#else
    ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);
#endif
    int m;
    cin >> dest >> m;
    int threshold = 0;
    v<pair<int, int>> edges(m);
    while (m--)
    {
        int a, b, c = 1;
        cin >> a >> b;
        edges.push_back({a, b});
        threshold += c;
        adj[a][b] += c;
        adj[b][a] += c;
    }
    while (threshold > 0)
    {
        memset(visited, 0, sizeof(visited));
        v<int> path;
        if (dfs(1, dest, threshold, path))
        {
            reverse(path.begin(), path.end());
            int n = path.size();
            int minWeight = 1e18;
            for (int i = 0; i < n - 1; i++)
                minWeight = min(minWeight, adj[path[i]][path[i + 1]]);
            for (int i = 0; i < n - 1; i++)
                adj[path[i]][path[i + 1]] -= minWeight,
                    adj[path[i + 1]][path[i]] += minWeight;
            ans += minWeight;
        }
        else
            threshold >>= 1;
    }
    source = DSU(dest + 1);
    v<bool> vis(dest + 1);
    dfs2(1, vis);
    for (int i = 1; i <= dest; i++)
        if (source.find(1) != source.find(i))
            source.unions(dest, i);
    v<pair<int, int>> removed;
    for (auto [x, y] : edges)
        if (source.find(x) != source.find(y))
            removed.emplace_back(x, y);
    cout << ans << endl;
    for (auto [x, y] : removed)
        cout << x << ' ' << y << endl;
}
