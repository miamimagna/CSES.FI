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
