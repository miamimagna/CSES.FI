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
int fav;
int n;
int dfs(int root, int p, v<v<int>> &adj, v<int> &sz)
{
    sz[root] = 1;
    bool flag = 1;
    for (int child : adj[root])
        if (child != p)
        {
            int x = dfs(child, root, adj, sz);
            if (x > n / 2)
                flag = 0;
            sz[root] += x;
        }
    int res = n - sz[root];
    if (res > n / 2)
        flag = 0;
    if (flag)
        fav = root;
    return sz[root];
}
signed main()
{
#ifdef LOCAL
    freopen("input.txt", "r", stdin);
    // freopen("output.txt", "w", stdout);
#else
    ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);
#endif
    cin >> n;
    v<v<int>> adj(n + 1);
    for (int i = 1; i < n; i++)
    {
        int x, y;
        cin >> x >> y;
        adj[x].push_back(y);
        adj[y].push_back(x);
    }
    v<int> sz(n + 1);
    dfs(1, 0, adj, sz);
    cout << fav << endl;
}
