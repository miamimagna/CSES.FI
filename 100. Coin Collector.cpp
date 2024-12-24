#include <algorithm>
#include <iostream>
#include <cstdio>
#include <vector>
using namespace std;
#define int long long
vector<vector<int>> adj;
int n;
vector<bool> visited;
void dfs(int v, vector<vector<int>> &adj, vector<int> &output)
{
    visited[v] = 1;
    for (auto u : adj[v])
        if (!visited[u])
            dfs(u, adj, output);
    output.push_back(v);
}
void scc(vector<vector<int>> &adj, vector<vector<int>> &components, vector<vector<int>> &adj_cond)
{
    vector<int> order;
    visited.assign(n, 0);

    for (int i = 0; i < n; i++)
        if (!visited[i])
            dfs(i, adj, order);

    vector<vector<int>> adj_rev(n);
    for (int i = 0; i < n; i++)
        for (int j : adj[i])
            adj_rev[j].push_back(i);

    visited.assign(n, 0);
    reverse(order.begin(), order.end());

    vector<int> roots(n, 0);

    // second series of dfs
    for (auto v : order)
        if (!visited[v])
        {
            vector<int> component;
            dfs(v, adj_rev, component);
            components.push_back(component);
            int root = *min_element(component.begin(), component.end());
            for (auto u : component)
                roots[u] = root;
        }

    adj_cond.assign(n, {});
    for (int v = 0; v < n; v++)
        for (int u : adj[v])
            if (roots[v] != roots[u])
                adj_cond[roots[v]].push_back(roots[u]);
}
int dfs(int i, vector<vector<int>> &adj, vector<int> &cost, vector<int> &dp)
{
    visited[i] = 1;
    int c = cost[i];
    int mx = 0;
    for (int child : adj[i])
        if (visited[child])
            mx = max(mx, dp[child]);
        else
            mx = max(mx, dfs(child, adj, cost, dp));
    return dp[i] = c + mx;
}
signed main()
{
#ifdef LOCAL
    freopen("input.txt", "r", stdin);
#endif
    int m;
    cin >> n >> m;
    vector<int> cost(n);
    for (auto &x : cost)
        cin >> x;
    adj.resize(n);
    while (m--)
    {
        int x, y;
        cin >> x >> y;
        x--, y--;
        adj[x].push_back(y);
    }
    vector<vector<int>> components, adj_con;
    scc(adj, components, adj_con);
    vector<int> roots;
    for (auto x : components)
    {
        int mn = 1e9, c = 0;
        for (int y : x)
            mn = min(mn, y), c += cost[y];
        cost[mn] = c;
        roots.push_back(mn);
    }
    vector<int> dp(n);
    visited.assign(n, 0);
    int mx = 0;
    for (int x : roots)
        if (!visited[x])
            mx = max(mx, dfs(x, adj_con, cost, dp));
    cout << mx << endl;
}
