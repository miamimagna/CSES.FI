#include <iostream>
#include <vector>
#include <cstdio>
#include <algorithm>
using namespace std;
/*
alright here is the thing, the max distance can either be in direction of either of child or of parent
so we need to preprocess to get the distances of all branches for every node..
now answer will be max(max_branch_depth, max_parent_depth), where max_parent_depth will be maximum depth that parent can have on any other branch
parent can have one of following branch as highest:
1. maximum depth branch in case of every child except the one contained in max_depth_branch
2. for max_depth_branch, we need second max depth branch
3. in direction of parent of parent branch
here we can clearly observe that we only need to store max_depth and second depth branch for answer calculation
*/
using Graph = vector<vector<int>>;
Graph adj;
vector<int> vis;
vector<tuple<int, int, int>> dp;
// preprocess all answers to be stored in dp as (max, smax, max_child)
tuple<int, int, int> dfs_preprocessing(int i)
{
    int mx = 0, smx = 0, mxc = -1;
    vis[i] = 1;
    for (int child : adj[i])
    {
        if (vis[child])
            continue;
        auto [cmx, csmx, cmxc] = dfs_preprocessing(child);
        if (cmx + 1 > mx)
            smx = mx, mx = cmx + 1, mxc = child;
        else if (cmx + 1 > smx)
            smx = cmx + 1;
    }
    return dp[i] = {mx, smx, mxc};
}
void dfs(int i, vector<int> &ans, int pcnt = -1)
{
    vis[i] = 1;
    auto [mx, smx, mxc] = dp[i];
    //every case will have answer either mx or pcnt + 1
    ans[i] = max({mx, smx, pcnt + 1});
    for (int child : adj[i])
    {
        if (vis[child])
            continue;
        int cost = 0;
        if (child == mxc)
            cost = smx;
        else
            cost = mx;
        cost = max(cost, pcnt + 1);
        dfs(child, ans, cost);
    }
}
int main()
{
#ifdef LOCAL
    freopen("input.txt", "r", stdin);
#endif
    int n;
    cin >> n;
    adj.resize(n + 1);
    vis.resize(n + 1);
    for (int i = 0; i < n - 1; i++)
    {
        int x, y;
        cin >> x >> y;
        adj[x].push_back(y);
        adj[y].push_back(x);
    }
    dp.resize(n + 1);
    // this preprocessing will store max depth branch, second max depth branch and which child has largest branch
    dfs_preprocessing(1);
    vis.assign(n + 1, 0);
    vector<int> ans(n + 1);
    // this is actual answer calculation depth first search
    dfs(1, ans);
    for (int i = 1; i <= n; i++)
        cout << ans[i] << ' ';
    cout << endl;
}
