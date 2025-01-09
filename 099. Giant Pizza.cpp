#include <cmath>
#include <iostream>
#include <cstdio>
#include <algorithm>
#include <vector>
#include <unordered_map>
#include <string>
#include <sstream>
#include <set>
#include <unordered_set>
using namespace std;
// preprocessing to make code easier
#define int long long
template <typename T>
using v = vector<T>;
int n, m;
int neg(int x)
{
    return x > m ? x - m : x + m;
}
vector<vector<int>> adj;
vector<bool> visited;
void dfs(int v, vector<vector<int>> &adj, vector<int> &output)
{
    visited[v] = 1;
    for (auto u : adj[v])
        if (!visited[u])
            dfs(u, adj, output);
    output.push_back(v);
}
v<int> scc(vector<vector<int>> &adj, vector<vector<int>> &components, vector<vector<int>> &adj_cond)
{
    int n = 2 * m + 1;
    components.clear(), adj_cond.clear();
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
    return roots;
}
void topo_dfs(int i, v<int> &ans, v<v<int>> &adj)
{
    visited[i] = 1;
    for (int u : adj[i])
        if (!visited[u])
            topo_dfs(u, ans, adj);
    ans.push_back(i);
}
signed main()
{
    cin >> n >> m;
    adj = v<v<int>>(2 * m + 1);
    unordered_set<int> exist;
    while (n--)
    {
        char chx, chy;
        int x, y;
        cin >> chx >> x >> chy >> y;
        if (chx == '-')
            x = neg(x);
        if (chy == '-')
            y = neg(y);
        exist.insert(x), exist.insert(y);
        // now for every a or b we add -a implies b and -b implies a
        adj[neg(x)].push_back(y);
        adj[neg(y)].push_back(x);
    }
    // get all strong connected components
    // get the scc graph adjacency list
    vector<vector<int>> components, adj_con;
    auto roots = scc(adj, components, adj_con);
    // check for contradiction, if found print impossible
    for (int i = 1; i <= m; i++)
        if (roots[i] == roots[neg(i)])
        {
            cout << "IMPOSSIBLE" << endl;
            return 0;
        }
    // perform topological sort on it
    v<int> order;
    visited = v<bool>(2 * m + 1);
    for (int i = 1; i <= 2 * m; i++)
        if (!visited[roots[i]])
            topo_dfs(roots[i], order, adj_con);
    reverse(order.begin(), order.end());
    // assign values to nodes
    unordered_map<int, int> mp;
    unordered_map<int, char> ans;
    for (int i = 0; i < order.size(); i++)
        mp[order[i]] = i;
    // print results
    for (int i = 1; i <= m; i++)
    {
        if (exist.count(i) && exist.count(neg(i)))
        {
            if (mp[roots[i]] < mp[roots[neg(i)]])
                ans[i] = '-';
            else
                ans[i] = '+';
        }
        else if (exist.count(i))
            ans[i] = '+';
        else
            ans[i] = '-';
        cout << ans[i] << ' ';
    }
    cout << endl;
}
