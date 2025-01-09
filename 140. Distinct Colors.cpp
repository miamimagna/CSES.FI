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
// #define int long long
template <typename T>
using v = vector<T>;
v<int> ans;
unordered_set<int> dfs(int i, int p, v<v<int>> &adj, v<int> &colors)
{
    unordered_set<int> s;
    s.insert(colors[i]);
    for (int child : adj[i])
        if (child != p)
        {
            auto cs = dfs(child, i, adj, colors);
            if (s.size() < cs.size())
                swap(s, cs);
            for (auto x : cs)
                s.insert(x);
        }
    ans[i] = s.size();
    return s;
}
signed main()
{
#ifdef LOCAL
    freopen("input.txt", "r", stdin);
#endif
    int n;
    cin >> n;
    v<int> colors(n + 1);
    for (int i = 1; i <= n; i++)
        cin >> colors[i];
    v<v<int>> adj(n + 1);
    for (int i = 1; i < n; i++)
    {
        int x, y;
        cin >> x >> y;
        adj[x].push_back(y);
        adj[y].push_back(x);
    }
    ans = v<int>(n + 1);
    dfs(1, 0, adj, colors);
    for (int i = 1; i <= n; i++)
        cout << ans[i] << ' ';
    cout << endl;
}
