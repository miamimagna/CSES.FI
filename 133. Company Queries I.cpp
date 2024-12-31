#include <iostream>
#include <cstdio>
#include <vector>
#include <algorithm>
using namespace std;
#define int long long
vector<int> cur;
void dfs(int i, vector<vector<int>> &adj, vector<int> &answer, vector<vector<pair<int, int>>> &query)
{
    cur.push_back(i);
    int mx = cur.size();
    for (auto [depth, idx] : query[i])
        if (depth >= mx)
            answer[idx] = -1;
        else
            answer[idx] = cur[mx - 1 - depth];
    for (int child : adj[i])
        dfs(child, adj, answer, query);
    cur.pop_back();
}
signed main()
{
    int n, q;
    cin >> n >> q;
    vector<vector<int>> adj(n + 1);
    vector<vector<pair<int, int>>> query(n + 1);
    for (int i = 2; i <= n; i++)
    {
        int x;
        cin >> x;
        adj[x].push_back(i);
    }
    for (int i = 0; i < q; i++)
    {
        int node, x;
        cin >> node >> x;
        query[node].push_back({x, i});
    }
    vector<int> answer(q);
    dfs(1, adj, answer, query);
    for (auto x : answer)
        cout << x << endl;
}
/*
            *****BINARY LIFTING SOLUTION*******
#include <iostream>
#include <vector>
#include <utility>
#include <cmath>
using namespace std;
template <typename t>
using v = vector<t>;
class LCA
{
    int n, l;
    v<v<int>> up;
    v<int> tin, tout, height;
    void dfs(int root, int p, v<v<int>> &adj, int &timer, int h = 0)
    {
        // tin mark
        tin[root] = timer++;
        height[root] = h;
        up[root][0] = p;
        // create up
        for (int i = 1; i <= l; i++)
            up[root][i] = up[up[root][i - 1]][i - 1];
        // traverse child
        for (int child : adj[root])
            if (child != p)
                dfs(child, root, adj, timer, h + 1);
        // tout mark
        tout[root] = timer++;
    }
    LCA(int n) : n(n), l(ceil(log2(n))), up(n, v<int>(l + 1)), tin(n), tout(n), height(n) {}
    bool is_ancestor(int u, int v)
    {
        return (tin[u] <= tin[v] && tout[u] >= tout[v]);
    }

public:
    LCA(v<v<int>> &adj, int root) : LCA((int)adj.size())
    {
        int timer = 0;
        dfs(root, root, adj, timer);
    }
    int lca(int u, int v)
    {
        if (is_ancestor(u, v))
            return u;
        if (is_ancestor(v, u))
            return v;
        for (int i = up[u].size() - 1; i >= 0; i--)
            if (!is_ancestor(up[u][i], v))
                u = up[u][i];
        return up[u][0];
    }
    int get_ancestor(int u, int k)
    {
        if (k > height[u])
            return -1;
        for (int i = l; i >= 0; i--)
            if ((1 << i) < k)
                u = up[u][i], k -= (1 << i);
        return up[u][0];
    }
};
#include <cstdio>
int main()
{
#ifdef LOCAL
    freopen("input.txt", "r", stdin);
#endif
    int n, q;
    cin >> n >> q;
    v<v<int>> adj(n + 1);
    for (int i = 2; i <= n; i++)
    {
        int x;
        cin >> x;
        adj[x].push_back(i);
        adj[i].push_back(x);
    }
    LCA lca(adj, 1);
    while (q--)
    {
        int u, k;
        cin >> u >> k;
        cout << lca.get_ancestor(u, k) << endl;
    }
}
*/
