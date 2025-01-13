#include <iostream>
#include <vector>
using namespace std;
#define int long long
template <typename t>
using v = vector<t>;
#define N 200001
v<int> adj[N];
int subsize[N]{};
bool cenmark[N];
int dfs(int root, int parent = -1)
{
    subsize[root] = 1;
    for (int child : adj[root])
        if (child != parent && !cenmark[child])
            subsize[root] += dfs(child, root);
    return subsize[root];
}
int get_centroid(int root, int desired, int parent = -1)
{
    for (int child : adj[root])
        if (child != parent && !cenmark[child] && subsize[child] > desired)
            return get_centroid(child, desired, root);
    return root;
}
int cnt[N], total_cnt[N]{1};
int subtree_depth = 0, mx_depth = 0, ans = 0, a, b;
void get_cnt(int node, int parent, int depth = 1)
{
    if (depth > b)
        return;
    subtree_depth = max(subtree_depth, depth);
    cnt[depth]++;
    for (int child : adj[node])
        if (child != parent && !cenmark[child])
            get_cnt(child, node, depth + 1);
}
void decompose_tree(int root)
{
    int centroid = get_centroid(root, dfs(root) >> 1);
    cenmark[centroid] = 1;
    mx_depth = 0;
    long long partial_sum_init = (a == 1 ? 1ll : 0ll);
    for (int child : adj[centroid])
        if (!cenmark[child])
        {
            subtree_depth = 0;
            get_cnt(child, centroid);
 
            long long partial_sum = partial_sum_init;
            for (int depth = 1; depth <= subtree_depth; depth++)
            {
                ans += partial_sum * cnt[depth];
 
                int dremove = b - depth;
                if (dremove >= 0)
                    partial_sum -= total_cnt[dremove];
                int dadd = a - (depth + 1);
                if (dadd >= 0)
                    partial_sum += total_cnt[dadd];
            }
 
            for (int depth = a - 1; depth <= b - 1 && depth <= subtree_depth; depth++)
                partial_sum_init += cnt[depth];
 
            for (int depth = 1; depth <= subtree_depth; depth++)
                total_cnt[depth] += cnt[depth];
            mx_depth = max(mx_depth, subtree_depth);
 
            fill(cnt, cnt + subtree_depth + 1, 0);
        }
 
    fill(total_cnt + 1, total_cnt + mx_depth + 1, 0);
    for (int child : adj[centroid])
        if (!cenmark[child])
            decompose_tree(child);
}
signed main()
{
#ifdef LOCAL
    freopen("input.txt", "r", stdin);
#else
    ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);
#endif
    int n;
    cin >> n >> a >> b;
    for (int i = 1; i < n; i++)
    {
        int x, y;
        cin >> x >> y;
        adj[x].push_back(y);
        adj[y].push_back(x);
    }
    decompose_tree(1);
    cout << ans << endl;
}
/*
this one is even better but it speaks language of gods
#include <cmath>
#include <iostream>
#include <algorithm>
#include <vector>
#include <unordered_map>
#include <string>
#include <queue>
#include <set>
#include <unordered_set>
using namespace std;
// preprocessing to make code easier
#define int long long
template <typename T>
using v = vector<T>;
#define N 200001
v<int> adj[N];
int n, k1, k2;
long long ans;
// suf[i] -> sum of nodes having depth in range [i, inf)
int suf(deque<int> &suf, int idx)
{
    if (idx < 0)
        return suf[0];
    if (idx >= suf.size())
        return 0;
    return suf[idx];
}
// answer calculation is hard to understand but you will get it!
void mergeSuffixes(deque<int> &sa, deque<int> &sb)
{
    if (sa.size() < sb.size())
        swap(sa, sb);
    for (int i = 0; i < sb.size(); i++)
        ans += 1LL * (suf(sb, i) - suf(sb, i + 1)) * (suf(sa, k1 - i) - suf(sa, k2 - i + 1));
    for (int i = 0; i < sb.size(); i++)
        sa[i] += sb[i];
}

deque<int> dfs(int u, int p)
{
    deque<int> suf_parent{1};
    for (int v : adj[u])
        if (v != p)
        {
            deque<int> suf_child = dfs(v, u);
            // depth of child[0] should correspond to parent[1]
            suf_child.push_front(suf_child.front());
            mergeSuffixes(suf_parent, suf_child);
        }
    return suf_parent;
}

signed main()
{
#ifdef LOCAL
    freopen("input.txt", "r", stdin);
    // freopen("output.txt", "w", stdout);
#else
    ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);
#endif
    cin >> n >> k1 >> k2;
    for (int i = 1; i < n; i++)
    {
        int x, y;
        cin >> x >> y;
        adj[x].push_back(y);
        adj[y].push_back(x);
    }
    dfs(1, -1);
    cout << ans << endl;
    return 0;
}
*/
