/*
miami here!!
alright this problem took me 5-6 hours of coding to do it properly... because I wrote it from scartch!
so the first thing we need to solve this problem is to know the structure of the graph:
in this graph, each element has indegree of 1...
therefore if we continue to proceed with parents one by one, we will never reach end
hence for every node in graph, it must be one of following two:
1. it is part of a cycle
2. it is a branch that is connected to cycle
moreover this graph can have multiple connected components... so if some nodes lie in two different componenets,
it would be simple impossible to connect them
so to solve it we need to consider 3 different scenarios
1. both nodes are part of cycle:
    (a) if both are part of cycle, they will always be reachable, in such cases, the length between two will be difference in tin
    (b) but if the difference comes out negative, that should be added to length of cycle to get out answer(it is due to order of dfs)
2. if one is part of branch and one is part of cycle
    (a) we can't go from cycle node to branch as we can't get out of cycle...
    (b) for any branch connected to cycle, it will have two parts...
        (i) the branch part that will be connected to cycle(distance from branch node to root of branch on cycle)
        (ii) the cycle part that will be dsitance from root of branch on cycle to cycle node
3. if both are branch node:
    (a) if tin[from] is greater than tin[to], then it is impossible to go to it
    (b) otherwise, there can be one pretty specific case(tin in given in bracket):
      1(6) -> 2(5) -> 3(4)
                        \
                          -> 4(3) -> 7(2) -> (cycle)
                        /
            6(5) -> 5(4)
        in these cases, the ancestor might be on other branch, hence we need to check if ancestor is right one or not!
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
v<v<int>> up;
// it basically tells kth ancestor of someone.. that's all we need here
int get_kth_ancestor(int u, int k)
{
    if (!k)
        return u;
    for (int i = ceil(log2(k)); i >= 0; i--)
        if ((1ll << i) < k)
            u = up[u][i], k -= (1ll << i);
    return up[u][0];
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
signed main()
{
#ifdef LOCAL
    freopen("input.txt", "r", stdin);
#endif
    ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);
    int q;
    cin >> n >> q;
    // initializer
    parent.resize(n + 1);
    vis.resize(n + 1);
    iscycle.resize(n + 1);
    root.assign(n + 1, -1);
    up.assign(n + 1, v<int>(ceil(log2(n + 1))));
    tin.assign(n + 1, -1);
    cycle = branches = connected = DSU(n + 1);
    // parent and binary lifting array making
    for (int i = 1, x; i <= n; i++)
        cin >> x,
            parent[i] = x, up[i][0] = x;
    // binary lifting preprocessing
    for (int i = 1; i < up[0].size(); i++)
        for (int j = 1; j <= n; j++)
            up[j][i] = up[up[j][i - 1]][i - 1];
    // building all the important utilities
    for (int i = 1; i <= n; i++)
        if (!vis[i])
            dfs(i);
    v<int> ans;
    while (q--)
    {
        int x, y;
        cin >> x >> y;
        // if not connected return -1(obviously)
        if (x == y)
            ans.push_back(0);
        else if (connected.find(x) != connected.find(y))
            ans.push_back(-1);
        else
        {
            // if both in cycle
            if (iscycle[x] && iscycle[y])
                ans.push_back(findmincycle(x, y));
            // you can't reach branch from cycle
            else if (iscycle[x] && !iscycle[y])
                ans.push_back(-1);
            // if one cycle and one branch(surely it will reach!)
            else if (!iscycle[x] && iscycle[y])
            {
                int first = root[x];
                int cylen = first == y ? 0 : findmincycle(first, y);
                int bralen = tin[x] - tin[first];
                ans.push_back(bralen + cylen);
            }
            // if both are branches
            else
                // if x is ancestor of y
                if (tin[x] < tin[y])
                    ans.push_back(-1);
                // else if it is actually in same branch then push it else -1
                else
                    ans.push_back(get_kth_ancestor(x, tin[x] - tin[y]) == y ? tin[x] - tin[y] : -1);
        }
    }
    for (auto x : ans)
        cout << x << endl;
}
