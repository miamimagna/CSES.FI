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
int adj[501][501], orig[501][501];
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
void dfs2(int node, v<int> &path)
{
    if (node == dest)
    {
        path.push_back(node);
        return;
    }
    for (int i = 1; i <= dest; i++)
        if (adj[node][i] == 0 && orig[node][i])
        {
            orig[node][i] = 0, path.push_back(node), dfs2(i, path);
            return;
        }
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
        orig[a][b] = 1;
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
    cout << ans << endl;
    while (ans--)
    {
        v<int> path;
        dfs2(1, path);
        cout << path.size() << endl;
        for (auto x : path)
            cout << x << ' ';
        cout << endl;
    }
}
