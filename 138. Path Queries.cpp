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
template <typename T>
using v = vector<T>;
#define int long long
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

        block_size = max((int)1, log_2[m] / 2);
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
    int getsize(int u)
    {
        return size[u];
    }
};
int dfs(int i, int p, v<v<int>> &adj, v<int> &sz, DSU &heavy, v<int> &top_dsu, v<int> &depth, v<int> &parent, int d = 0)
{
    depth[i] = d;
    parent[i] = p;
    for (int child : adj[i])
        if (child != p)
            sz[i] += dfs(child, i, adj, sz, heavy, top_dsu, depth, parent, d + 1);
    for (int child : adj[i])
        if (child != p && sz[child] >= sz[i] / 2 + (sz[i] & 1))
            heavy.unions(i, child), top_dsu[heavy.find(child)] = i;
    return sz[i];
}
class SegTreeRecur
{
    vector<int> a;
    int n;
    void build(vector<int> &arr, int idx, int l, int r)
    {
        if (l == r)
            a[idx] = arr[l];
        else
        {
            int mid = (l + r) >> 1;
            build(arr, idx << 1, l, mid);
            build(arr, idx << 1 | 1, mid + 1, r);
            a[idx] = a[idx << 1] + a[idx << 1 | 1];
        }
    }
    int sumHelper(int idx, int l, int r, int tl, int tr)
    {
        if (l > r)
            return 0;
        else if (tl == l && tr == r)
            return a[idx];
        else
        {
            int mid = (tl + tr) >> 1;
            return sumHelper(idx << 1, l, min(r, mid), tl, mid) + sumHelper(idx << 1 | 1, max(mid + 1, l), r, mid + 1, tr);
        }
    }
    void replaceHelper(int i, int idx, int x, int l, int r)
    {
        if (l == r)
        {
            a[i] = x;
            return;
        }
        else if (idx <= (l + r) >> 1)
            replaceHelper(2 * i, idx, x, l, (l + r) >> 1);
        else
            replaceHelper(2 * i + 1, idx, x, ((l + r) >> 1) + 1, r);
        a[i] = a[2 * i] + a[2 * i + 1];
    }
    void helperIncrease(int ind, int l, int r, int i, int inc)
    {
        a[ind] += inc;
        if (l != r)
        {
            if (i <= (l + r) >> 1)
                helperIncrease(ind << 1, l, (l + r) >> 1, i, inc);
            else
                helperIncrease(ind << 1 | 1, (l + r) >> 1 | 1, r, i, inc);
        }
    }

public:
    SegTreeRecur() = default;
    SegTreeRecur(int nn) : a(4 * nn), n(nn) {}
    SegTreeRecur(vector<int> &arr) : SegTreeRecur((int)arr.size())
    {
        build(arr, 1, 0, arr.size() - 1);
    }
    int sum(int l, int r)
    {
        return sumHelper(1, l, r, 0, n - 1);
    }
    void replace(int idx, int x)
    {
        replaceHelper(1, idx, x, 0, n - 1);
    }
    void increase(int i, int inc)
    {
        helperIncrease(1, 0, n - 1, i, inc);
    }
};
signed main()
{
#ifdef LOCAL
    freopen("input.txt", "r", stdin);
    // freopen("output.txt", "w", stdout);
#else
    ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);
#endif
    int n, q;
    cin >> n >> q;
    v<v<int>> adj(n + 1);
    v<int> values(n + 1), sz(n + 1, 1);
    DSU heavy(n + 1);
    v<int> top_dsu(n + 1), depth(n + 1), parent(n + 1);
    for (int i = 1; i <= n; i++)
        cin >> values[i], top_dsu[i] = i;
    for (int i = 1; i < n; i++)
    {
        int x, y;
        cin >> x >> y;
        adj[x].push_back(y);
        adj[y].push_back(x);
    }
    LCA lc(adj, 1);
    dfs(1, 0, adj, sz, heavy, top_dsu, depth, parent);
    unordered_map<int, SegTreeRecur> heavyseg;
    // for any node, index would be depth[i] - depth[top_dsu[i]]
    for (int i = 0; i <= n; i++)
    {
        int root = heavy.find(i);
        if (heavy.getsize(root) == 1)
            continue;
        if (!heavyseg.count(root))
            heavyseg[root] = SegTreeRecur(heavy.getsize(root));
        heavyseg[root].replace(depth[i] - depth[top_dsu[root]], values[i]);
    }
    while (q--)
    {
        int type;
        cin >> type;
        // print sum of path
        if (type == 2)
        {
            int a;
            cin >> a;
            int res = 0;
            while (a)
            {
                int root = heavy.find(a);
                int sz = heavy.getsize(root);
                if (sz == 1)
                    res += values[a], a = parent[a];
                else
                    res += heavyseg[root].sum(0, depth[a] - depth[top_dsu[root]]), a = parent[top_dsu[root]];
            }
            cout << res << endl;
        }
        else
        {
            int a, b;
            cin >> a >> b;
            values[a] = b;
            int root = heavy.find(a);
            int sz = heavy.getsize(root);
            if (sz != 1)
                heavyseg[root].replace(depth[a] - depth[top_dsu[root]], b);
        }
    }
}
