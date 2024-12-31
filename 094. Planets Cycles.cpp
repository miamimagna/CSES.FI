/*
I used the previous solution in it but actually, we needed only two things, first is for every cycle node, answer is length of cycle
from rest of node, do a separate dfs till any cycle node comes, then answer[node] = answer[next] + 1, that's it! magic
*/
#include <iostream>
#include <vector>
#include <algorithm>
#include <unordered_map>
#include <cmath>
using namespace std;
#define int long long
template <typename t>
using v = vector<t>;
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
/*
data structure overview:
parent array: parent of each element(as adjacency list of every element consist of only one element)
root array: store the root element of each branch that is connecting point from branch to cycle
tin: the entry time of every element in dfs
vis: visited array for dfs
iscycle: tell if any node is part of cycle or not, if not it must be part of branch
cycle: dsu which stores sets of elements of single cycle
branches: dsu which stores sets of elements of single branch
cyclelength: the map will store the dsu-head of every cycle -> length of the cycle
 */
int n;
v<int> parent, root, tin;
v<bool> vis, iscycle;
DSU cycle(1), branches(1), connected(1);
unordered_map<int, int> cyclelength;
// here return values are [cycle_making_element, tin]
pair<int, int> dfs(int node)
{
    vis[node] = true;
    int child = parent[node];
    connected.unions(child, node);
    if (vis[child])
    {
        if (root[child] != -1)
            branches.unions(node, child);
        else
            iscycle[node] = 1;
        if (node == child)
            cyclelength[node] = 1;
        root[node] = root[child] == -1 ? node : root[child];
        tin[node] = tin[child] + 1;
        return {root[child] == -1 ? child : -root[node], tin[node]};
    }
    else
    {
        auto [cycle_maker, tinn] = dfs(child);
        if (cycle_maker > 0)
        {
            iscycle[node] = 1;
            root[node] = node;
            cycle.unions(node, child);
            tin[node] = tinn + 1;
            if (cycle_maker == node)
                cyclelength[cycle.find(node)] = tin[node] + 1;
            return {cycle_maker == node ? -cycle_maker : cycle_maker, tin[node]};
        }
        else
        {
            branches.unions(node, child);
            root[node] = -cycle_maker;
            tin[node] = tinn + 1;
            return {cycle_maker, tin[node]};
        }
    }
}
int findmincycle(int x, int y)
{
    int tx = tin[x], ty = tin[y];
    if (tx > ty)
        return tx - ty;
    else
    {
        int cylen = cyclelength[cycle.find(x)];
        return cylen - (ty - tx);
    }
}
int get_answer(int node)
{
    if (iscycle[node])
        return cyclelength[cycle.find(node)];
    else
    {
        int first = root[node];
        int bralen = tin[node] - tin[first];
        int cylen = cyclelength[cycle.find(first)];
        return bralen + cylen;
    }
}
signed main()
{
#ifdef LOCAL
    freopen("input.txt", "r", stdin);
#endif
    ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);
    cin >> n;
    // initializer
    parent.resize(n + 1);
    vis.resize(n + 1);
    iscycle.resize(n + 1);
    root.assign(n + 1, -1);
    tin.assign(n + 1, -1);
    cycle = branches = connected = DSU(n + 1);
    // parent array making
    for (int i = 1, x; i <= n; i++)
        cin >> x,
            parent[i] = x;
    // building all the important utilities
    for (int i = 1; i <= n; i++)
        if (!vis[i])
            dfs(i);
    v<int> ans(n + 1);
    for (int i = 1; i <= n; i++)
        cout << get_answer(i) << ' ';
    cout << endl;
}
