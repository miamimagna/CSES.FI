#include <cstdio>
#include <iostream>
#include <vector>
#include <utility>
#include <queue>
#include <algorithm>
#include <set>
using namespace std;
// preprocessing to make code easier 
template <typename T> 
using v = vector<T>; 
#define sz size() 
#define pb push_back 
#define eb emplace_back 
#define int long long
int mod = 1e9 + 7;
class DSU
{
public:
    v<int> parent, size;

    DSU(int n) : parent(n), size(n, 1)
    {
        for (int i = 0; i < n; i++)
            parent[i] = i;
    }
    int find(int u)
    {
        // path compression
        return parent[u] == u ? u : parent[u] = find(parent[u]);
    }
    void unions(int u, int v)
    {
        // union by size
        u = find(u), v = find(v);
        if (u == v)
            return;
        if (size[u] < size[v])
            swap(u, v);
        parent[v] = u;
        size[u] += size[v];
    }
};
void solve(){
    int n, m;
    cin >> n >> m;
    v<tuple<int, int, int>> edges;
    int components = n, mxsize = 1;
    DSU dsu(n + 1);
    while(m --){
        int from, to;
        cin>>from >> to;
        if(dsu.find(from) != dsu.find(to))
            components--,
            dsu.unions(from, to),
            mxsize = max(mxsize, dsu.size[dsu.find(from)]);
        cout << components << ' ' << mxsize << endl;
    }
}
signed main()
{
#ifdef LOCAL
    freopen("input.txt", "r", stdin);
#endif
    solve();
}
