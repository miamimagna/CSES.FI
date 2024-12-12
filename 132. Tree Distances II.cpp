#include <iostream>
#include <cstdio>
#include <vector>
#include <algorithm>
using namespace std;
#define int long long
int n;
vector<vector<int>> adj;
vector<int> vis;
vector<pair<int, int>> dp;
pair<int, int> dfs_preprocess(int i)
{
    vis[i] = 1;
    int cnt = 1, dist = 0;
    for (int child : adj[i])
    {
        if (vis[child])
            continue;
        auto [ccnt, cdist] = dfs_preprocess(child);
        cnt += ccnt;
        dist += ccnt + cdist;
    }
    return dp[i] = {cnt, dist};
}
vector<int> ans;
void dfs(int i, int pcost = 0)
{
    vis[i] = 1;
    auto [cnt, dist] = dp[i];
    pcost -= (cnt + dist);
    if (pcost < 0)
        pcost = 0;
    ans[i] = dist + (n - cnt) + pcost;
    for (int child : adj[i])
    {
        if (vis[child])
            continue;
        dfs(child, ans[i]);
    }
}
signed main()
{
    cin >> n;
    adj.resize(n + 1);
    vis.resize(n + 1);
    dp.resize(n + 1);
    for (int i = 0; i < n - 1; i++)
    {
        int x, y;
        cin >> x >> y;
        adj[x].push_back(y);
        adj[y].push_back(x);
    }
    dfs_preprocess(1);
    vis.assign(n + 1, 0);
    ans.resize(n + 1);
    dfs(1);
    for (int i = 1; i <= n; i++)
        cout << ans[i] << ' ';
    cout << endl;
}
