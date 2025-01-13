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
int cnt[N]{1};
int mx_depth = 0, ans = 0, k;
void get_cnt(int node, int parent, bool filling, int depth = 1)
{
    if (depth > k)
        return;
    mx_depth = max(mx_depth, depth);
    if (filling)
        cnt[depth]++;
    else
        ans += cnt[k - depth];
    for (int child : adj[node])
        if (child != parent && !cenmark[child])
            get_cnt(child, node, filling, depth + 1);
}
void decompose_tree(int root)
{
    int centroid = get_centroid(root, dfs(root) >> 1);
    cenmark[centroid] = 1;
    mx_depth = 0;
    for (int child : adj[centroid])
        if (!cenmark[child])
            get_cnt(child, centroid, 0),
                get_cnt(child, centroid, 1);
    fill(cnt + 1, cnt + mx_depth + 1, 0);
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
    cin >> n >> k;
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
