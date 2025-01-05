#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;
template <typename t>
using v = vector<t>;
int used = 0;
v<int> res;
void hierholzer(int i, v<v<int>> &adj)
{
    while (adj[i].size())
    {
        int x = adj[i].back();
        adj[i].pop_back();
        used++;
        hierholzer(x, adj);
    }
    res.push_back(i);
}
int main()
{
#ifdef LOCAL
    freopen("input.txt", "r", stdin);
#endif
    int n, m;
    cin >> n >> m;
    v<int> indeg(n + 1);
    v<v<int>> adj(n + 1);
    for (int i = 0; i < m; i++)
    {
        int x, y;
        cin >> x >> y;
        indeg[y]++;
        adj[x].push_back(y);
    }
    for (int i = 2; i < n; i++)
        if (indeg[i] != adj[i].size())
        {
            cout << "IMPOSSIBLE" << endl;
            return 0;
        }
    if (adj[1].size() - indeg[1] != 1 || adj[n].size() - indeg[n] != -1)
    {
        cout << "IMPOSSIBLE" << endl;
        return 0;
    }
    hierholzer(1, adj);
    if (used != m)
    {
        cout << "IMPOSSIBLE" << endl;
        return 0;
    }
    reverse(res.begin(), res.end());
    for (auto x : res)
        cout << x << ' ';
    cout << endl;
}
