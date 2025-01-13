#include <algorithm>
#include <iostream>
#include <vector>
#include <string>
#include <bitset>
#include <cstring>
using namespace std;
#define int long long
template <typename t>
using v = vector<t>;
int n;
v<v<int>> adj;
v<int> order;
void dfs(int node)
{
    while (adj[node].size())
    {
        int child = adj[node].back();
        adj[node].pop_back();
        dfs(child);
    }
    order.push_back(node);
}
signed main()
{
#ifdef LOCAL
    freopen("input.txt", "r", stdin);
#endif
    int m;
    cin >> m;
    if (m == 1)
    {
        cout << "01" << endl;
        return 0;
    }
    n = 1 << (m - 1);
    adj = v<v<int>>(n);
    for (int i = 0; i < n; i++)
        adj[i].push_back((i << 1) % n),
            adj[i].push_back(adj[i].back() + 1);
    dfs(0);
    string s;
    reverse(order.begin(), order.end());
    bitset<15> b(order.front());
    for (int i = 0; i < m - 1; i++)
        s += b[i] ? '1' : '0';
    for (int i = 1; i < order.size(); i++)
        s += order[i] & 1 ? '1' : '0';
    cout << s << endl;
}
