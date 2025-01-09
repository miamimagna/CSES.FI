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
class SegTreeRecur
{
    vector<int> a;
    int n;
    void build(vector<int> &arr, int idx, int l, int r)
    {
        if (l == r)
            a[idx] = arr[l];
        else
        {
            int mid = (l + r) >> 1;
            build(arr, idx << 1, l, mid);
            build(arr, idx << 1 | 1, mid + 1, r);
            a[idx] = a[idx << 1] + a[idx << 1 | 1];
        }
    }
    int sumHelper(int idx, int l, int r, int tl, int tr)
    {
        if (l > r)
            return 0;
        else if (tl == l && tr == r)
            return a[idx];
        else
        {
            int mid = (tl + tr) >> 1;
            return sumHelper(idx << 1, l, min(r, mid), tl, mid) + sumHelper(idx << 1 | 1, max(mid + 1, l), r, mid + 1, tr);
        }
    }
    void replaceHelper(int i, int idx, int x, int l, int r)
    {
        if (l == r)
        {
            a[i] = x;
            return;
        }
        else if (idx <= (l + r) >> 1)
            replaceHelper(2 * i, idx, x, l, (l + r) >> 1);
        else
            replaceHelper(2 * i + 1, idx, x, ((l + r) >> 1) + 1, r);
        a[i] = a[2 * i] + a[2 * i + 1];
    }
    void helperIncrease(int ind, int l, int r, int i, int inc)
    {
        a[ind] += inc;
        if (l != r)
        {
            if (i <= (l + r) >> 1)
                helperIncrease(ind << 1, l, (l + r) >> 1, i, inc);
            else
                helperIncrease(ind << 1 | 1, (l + r) >> 1 | 1, r, i, inc);
        }
    }

public:
    SegTreeRecur(int nn) : a(4 * nn), n(nn) {}
    SegTreeRecur(vector<int> &arr) : SegTreeRecur((int)arr.size())
    {
        build(arr, 1, 0, arr.size() - 1);
    }
    int sum(int l, int r)
    {
        return sumHelper(1, l, r, 0, n - 1);
    }
    void replace(int idx, int x)
    {
        replaceHelper(1, idx, x, 0, n - 1);
    }
    void increase(int i, int inc)
    {
        helperIncrease(1, 0, n - 1, i, inc);
    }
};
v<int> order;
int dfs(int i, int p, v<v<int>> &adj, v<int> &cnt)
{
    order.push_back(i);
    int count = 0;
    for (int child : adj[i])
        if (child != p)
            count += dfs(child, i, adj, cnt);
    return cnt[i] = count + 1;
}
signed main()
{
#ifdef LOCAL
    freopen("input.txt", "r", stdin);
#endif
    int n, q;
    cin >> n >> q;
    v<int> values(n + 1);
    v<v<int>> adj(n + 1);
    for (int i = 1; i <= n; i++)
        cin >> values[i];
    for (int i = 1; i < n; i++)
    {
        int x, y;
        cin >> x >> y;
        adj[x].push_back(y);
        adj[y].push_back(x);
    }
    v<int> cnts(n + 1);
    dfs(1, 0, adj, cnts);
    v<int> order_cnts(order.size()), idx(n + 1);
    for (int i = 0; i < order.size(); i++)
        order_cnts[i] = values[order[i]], idx[order[i]] = i;
    SegTreeRecur st(order_cnts);
    while (q--)
    {
        int type;
        cin >> type;
        // update value
        if (type == 1)
        {
            int s, x;
            cin >> s >> x;
            st.replace(idx[s], x);
        }
        // show sum
        else
        {
            int s;
            cin >> s;
            int size = cnts[s];
            int i = idx[s];
            cout << st.sum(i, i + size - 1) << endl;
        }
    }
}
