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
// you can use any lca algo, I'm using best I know
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
 
        block_size = max(1ll, log_2[m] / 2);
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
 
void dfs(int i, int p, v<v<int>> &adj, v<int> &depth, int d = 0)
{
    depth[i] = d;
    for (int child : adj[i])
        if (child != p)
            dfs(child, i, adj, depth, d + 1);
}
signed main()
{
#ifdef LOCAL
    freopen("input.txt", "r", stdin);
#endif
    ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);
    int n, q;
    cin >> n >> q;
    v<v<int>> adj(n + 1);
    for (int i = 0; i < n - 1; i++)
    {
        int x, y;
        cin >> x >> y;
        adj[x].push_back(y);
        adj[y].push_back(x);
    }
    LCA lc(adj, 1);
    v<int> depth(n + 1);
    dfs(1, 0, adj, depth);
    while (q--)
    {
        int a, b;
        cin >> a >> b;
        int lca = lc.lca(a, b);
        cout << depth[a] + depth[b] - depth[lca] * 2 << endl;
    }
}
