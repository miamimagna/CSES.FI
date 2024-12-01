#include <iostream>
#include <algorithm>
#include <vector>
#include <cstdio>
using namespace std;
class Segment
{
    vector<int> a;
    int n;
    int sum(int i, int tl, int tr, int l, int r)
    {
        if (l > r)
            return 0;
        else if (tl == l && tr == r)
            return a[i];
        int tm = (tl + tr) >> 1;
        return sum(i << 1, tl, tm, l, min(r, tm)) + sum(i << 1 | 1, tm + 1, tr, max(l, tm + 1), r);
    }
    void update(int i, int tl, int tr, int pos, int delta)
    {
        if (tl == tr)
            a[i] += delta;
        else
        {
            int tm = (tl + tr) >> 1;
            if (pos <= tm)
                update(i << 1, tl, tm, pos, delta);
            else
                update(i << 1 | 1, tm + 1, tr, pos, delta);
            a[i] = a[i << 1] + a[i << 1 | 1];
        }
    }
    void build(vector<int> &arr, int i, int l, int r)
    {
        if (l == r)
            a[i] = arr[l];
        else
        {
            int mid = (l + r) >> 1;
            build(arr, i << 1, l, mid);
            build(arr, i << 1 | 1, mid + 1, r);
            a[i] = a[i << 1] + a[i << 1 | 1];
        }
    }

public:
    Segment(int nn) : a(nn << 2), n(nn) {}
    Segment(vector<int> &arr) : Segment((int)arr.size())
    {
        build(arr, 1, 0, n - 1);
    }
    int sum(int l, int r)
    {
        return sum(1, 0, n - 1, l, r);
    }
    void update(int pos, int delta)
    {
        update(1, 0, n - 1, pos, delta);
    }
};
#include <utility>
#include <unordered_map>
using query = tuple<char, int, int>;
int main()
{
#ifdef LOCAL
    freopen("input.txt", "r", stdin);
#endif
    ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);
    int n = 0, q = 0;
    cin >> n >> q;
    vector<int> a(n);
    vector<query> qry(q);
    for (auto &x : a)
        cin >> x;
    for (auto &[ch, a, b] : qry)
        cin >> ch >> a >> b;
    unordered_map<int, int> mp(4e5);
    vector<int> nodes;
    for (int x : a)
        if (!mp.count(x))
            mp[x] = 0, nodes.push_back(x);
    for (auto &[ch, a, b] : qry)
        if (ch == '!' && !mp.count(b))
            mp[b] = 0, nodes.push_back(b);
    sort(nodes.begin(), nodes.end());
    for (int i = 0; i < (int)nodes.size(); i++)
        mp[nodes[i]] = i;
    vector<int> cnt(nodes.size());
    for (int i = 0; i < n; i++)
        cnt[mp[a[i]]] += 1;
    Segment st(cnt);
    for (auto [ch, x, y] : qry)
        if (ch == '!')
        {
            x--;
            int i = mp[a[x]], j = mp[y];
            st.update(i, -1), st.update(j, +1);
            a[x] = y;
        }
        else
        {
            if (x > nodes.back() || y < nodes.front())
                cout << 0 << endl;
            else
            {
                int i = lower_bound(nodes.begin(), nodes.end(), x) - nodes.begin();
                int j = upper_bound(nodes.begin(), nodes.end(), y) - nodes.begin() - 1;
                cout << st.sum(i, j) << endl;
            }
        }
}
