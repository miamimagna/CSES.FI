#include <iostream>
#include <vector>
#include <algorithm>
#include <utility>
#include <cmath>
using namespace std;
template <typename t>
using v = vector<t>;
// this has some of the most cheesy name in algorithm(don't remember the name google it!)
class LCA
{
    // it runs in O(n) time complexity, source: trust me!(just kidding! cp-algo)
    int n;
    v<v<int>> adj;

    int block_size, block_cnt;
    v<int> first_visit;
    v<int> euler_tour;
    v<int> height;
    v<int> log_2;
    v<v<int>> st;
    v<v<v<int>>> blocks;
    v<int> block_mask;

    void dfs(int v, int p, int h)
    {
        first_visit[v] = euler_tour.size();
        euler_tour.push_back(v);
        height[v] = h;

        for (int u : adj[v])
        {
            if (u == p)
                continue;
            dfs(u, v, h + 1);
            euler_tour.push_back(v);
        }
    }

    int min_by_h(int i, int j)
    {
        return height[euler_tour[i]] < height[euler_tour[j]] ? i : j;
    }

    void precompute_lca(int root)
    {
        // get euler tour & indices of first occurrences
        first_visit.assign(n, -1);
        height.assign(n, 0);
        euler_tour.reserve(2 * n);
        dfs(root, -1, 0);

        // precompute all log values
        int m = euler_tour.size();
        log_2.reserve(m + 1);
        log_2.push_back(-1);
        for (int i = 1; i <= m; i++)
            log_2.push_back(log_2[i / 2] + 1);

        block_size = max(1, log_2[m] / 2);
        block_cnt = (m + block_size - 1) / block_size;

        // precompute minimum of each block and build sparse table
        st.assign(block_cnt, v<int>(log_2[block_cnt] + 1));
        for (int i = 0, j = 0, b = 0; i < m; i++, j++)
        {
            if (j == block_size)
                j = 0, b++;
            if (j == 0 || min_by_h(i, st[b][0]) == i)
                st[b][0] = i;
        }
        for (int l = 1; l <= log_2[block_cnt]; l++)
        {
            for (int i = 0; i < block_cnt; i++)
            {
                int ni = i + (1 << (l - 1));
                if (ni >= block_cnt)
                    st[i][l] = st[i][l - 1];
                else
                    st[i][l] = min_by_h(st[i][l - 1], st[ni][l - 1]);
            }
        }

        // precompute mask for each block
        block_mask.assign(block_cnt, 0);
        for (int i = 0, j = 0, b = 0; i < m; i++, j++)
        {
            if (j == block_size)
                j = 0, b++;
            if (j > 0 && (i >= m || min_by_h(i - 1, i) == i - 1))
                block_mask[b] += 1 << (j - 1);
        }

        // precompute RMQ for each unique block
        int possibilities = 1 << (block_size - 1);
        blocks.resize(possibilities);
        for (int b = 0; b < block_cnt; b++)
        {
            int mask = block_mask[b];
            if (!blocks[mask].empty())
                continue;
            blocks[mask].assign(block_size, v<int>(block_size));
            for (int l = 0; l < block_size; l++)
            {
                blocks[mask][l][l] = l;
                for (int r = l + 1; r < block_size; r++)
                {
                    blocks[mask][l][r] = blocks[mask][l][r - 1];
                    if (b * block_size + r < m)
                        blocks[mask][l][r] = min_by_h(b * block_size + blocks[mask][l][r],
                                                      b * block_size + r) -
                                             b * block_size;
                }
            }
        }
    }

    int lca_in_block(int b, int l, int r)
    {
        return blocks[block_mask[b]][l][r] + b * block_size;
    }

public:
    LCA(v<v<int>> &adj, int root) : n((int)adj.size()), adj(adj)
    {
        precompute_lca(root);
    }
    int lca(int v, int u)
    {
        int l = first_visit[v];
        int r = first_visit[u];
        if (l > r)
            swap(l, r);
        int bl = l / block_size;
        int br = r / block_size;
        if (bl == br)
            return euler_tour[lca_in_block(bl, l % block_size, r % block_size)];
        int ans1 = lca_in_block(bl, l % block_size, block_size - 1);
        int ans2 = lca_in_block(br, 0, r % block_size);
        int ans = min_by_h(ans1, ans2);
        if (bl + 1 < br)
        {
            int l = log_2[br - bl - 1];
            int ans3 = st[bl + 1][l];
            int ans4 = st[br - (1 << l)][l];
            ans = min_by_h(ans, min_by_h(ans3, ans4));
        }
        return euler_tour[ans];
    }
};
#include <cstdio>
int main()
{
#ifdef LOCAL
    freopen("input.txt", "r", stdin);
#endif
    ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);
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
        cout << lca.lca(u, k) << endl;
    }
}
/*
// euler tour + Segment Tree
class LCA
{
    v<int> a, euler, height, first;
    int n, hn;
    void dfs(int node, int p, v<v<int>> &adj, int h = 0)
    {
        first[node] = euler.size();
        euler.push_back(node);
        height[node] = h;
        for (int child : adj[node])
            if (child != p)
            {
                dfs(child, node, adj, h + 1);
                euler.push_back(node);
            }
    }
    int minmod(int l, int r)
    {
        return height[l] < height[r] ? l : r;
    }
    void build(int idx, int l, int r)
    {
        if (l == r)
            a[idx] = euler[l];
        else
        {
            int mid = (l + r) >> 1;
            build(idx << 1, l, mid);
            build(idx << 1 | 1, mid + 1, r);
            a[idx] = minmod(a[idx << 1], a[idx << 1 | 1]);
        }
    }
    int lca(int node, int b, int e, int L, int R)
    {
        if (b > R || e < L)
            return -1;
        if (b >= L && e <= R)
            return a[node];
        int mid = (b + e) >> 1;

        int left = lca(node << 1, b, mid, L, R);
        int right = lca(node << 1 | 1, mid + 1, e, L, R);
        if (left == -1)
            return right;
        if (right == -1)
            return left;
        return height[left] < height[right] ? left : right;
    }

public:
    LCA(v<v<int>> &adj, int root)
    {
        n = adj.size();
        height.resize(n);
        height.push_back(1e9);
        hn = n + 1;
        first.resize(n);
        dfs(root, -1, adj, 0);
        n = euler.size();
        a.resize(n << 2);
        build(1, 0, n - 1);
    }
    int lca(int l, int r)
    {
        auto [a, b] = minmax(first[l], first[r]);
        return lca(1, 0, n - 1, a, b);
    }
};
// binary lifting
class LCA
{
    int n, l;
    v<v<int>> up;
    v<int> tin, tout;
    void dfs(int root, int p, v<v<int>> &adj, int &timer)
    {
        // tin mark
        tin[root] = timer++;
        up[root][0] = p;
        // create up
        for (int i = 1; i <= l; i++)
            up[root][i] = up[up[root][i - 1]][i - 1];
        // traverse child
        for (int child : adj[root])
            if (child != p)
                dfs(child, root, adj, timer);
        // tout mark
        tout[root] = timer++;
    }
    LCA(int n) : n(n), l(ceil(log2(n))), up(n, v<int>(l + 1)), tin(n), tout(n) {}
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
};

*/
