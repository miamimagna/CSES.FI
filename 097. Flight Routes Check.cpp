#include <algorithm>
#include <iostream>
#include <cstdio>
#include <vector>
using namespace std;
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
  // order will store the order of nodes
    vector<int> order;
    visited.assign(n, 0);
    // forward dfs for getting order of decreasing tout
    for (int i = 0; i < n; i++)
        if (!visited[i])
            dfs(i, adj, order);

    vector<vector<int>> adj_rev(n);
    for (int i = 0; i < n; i++)
        for (int j : adj[i])
            adj_rev[j].push_back(i);
// reverse the list to get smallest tout
    visited.assign(n, 0);
    reverse(order.begin(), order.end());

    vector<int> roots(n, 0);

    // second series of dfs with reverse adj to get components
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
// condensed graph using components
    adj_cond.assign(n, {});
    for (int v = 0; v < n; v++)
        for (int u : adj[v])
            if (roots[v] != roots[u])
                adj_cond[roots[v]].push_back(roots[u]);
}
int main()
{
#ifdef LOCAL
    freopen("input.txt", "r", stdin);
#endif
    int m;
    cin >> n >> m;
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
    if (components.size() == 1)
        cout << "YES" << endl;
    else
    {
        cout << "NO" << endl;
        for (int i = 0; i < n; i++)
            for (int j : adj_con[i])
            {
                cout << j + 1 << ' ' << i + 1 << endl;
                return 0;
            }
        cout << components[0][0] + 1 << ' ' << components[1][0] << endl;
    }
}
