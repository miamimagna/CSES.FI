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
v<set<int>> adj;
v<int> res;
int edges_used = 0;
void traverse(int i)
{
  // until there is another edge, traverse that vertice and pop it
    while (adj[i].size())
    {
        int child = *adj[i].begin();
        adj[i].erase(child);
        adj[child].erase(i);
        edges_used++;
        traverse(child);
    }
    // push when no more edges... dunno how it works
    res.push_back(i);
}
signed main()
{
#ifdef LOCAL
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
    int n, m;
    cin >> n >> m;
    v<int> deg(n);
    n++;
    adj = v<set<int>>(n);
    for (int i = 0; i < m; i++)
    {
        int x, y;
        cin >> x >> y;
        deg[x - 1]++, deg[y - 1]++;
        adj[x].insert(y);
        adj[y].insert(x);
    }
    int cnt = 0;
    for (auto x : deg)
        if ((x & 1))
        {
            cout << "IMPOSSIBLE" << endl;
            return 0;
        }
    traverse(1);
    // alternate stack based approach
    // v<int> st{1}, res;
    // while (st.size())
    // {
    //     int v = st.back();
    //     if (adj[v].empty())
    //         res.push_back(v), st.pop_back();
    //     else
    //     {
    //         int child = *adj[v].begin();
    //         edges_used++;
    //         adj[v].erase(child);
    //         adj[child].erase(v);
    //         st.push_back(child);
    //     }
    // }
    if (edges_used < m)
    {
        cout << "IMPOSSIBLE" << endl;
    }
    else
        for (auto x : res)
            cout << x << ' ';
    cout << endl;
}
