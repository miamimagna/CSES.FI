#include <iostream>
#include <cstdio>
#include <vector>
#include <utility>
#include <algorithm>
using namespace std;
/*
huge thanks to MushfiqTalha brother!!! It would've been impossible without you brother
https://codeforces.com/blog/entry/132375
 */
#define int long long
// yes this is a segment tree
class Segment
{
    vector<int> prefix;

public:
    Segment(vector<int> a) : prefix((int)a.size() + 1)
    {
        prefix[0] = 0;
        for (int i = 0; i < (int)a.size(); i++)
            prefix[i + 1] = prefix[i] + a[i];
    }
    int sum(int l, int r)
    {
        return prefix[r + 1] - prefix[l];
    }
};
signed main()
{
#ifdef LOCAL
    freopen("input.txt", "r", stdin);
#endif
    ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);
    int n, q;
    cin >> n >> q;
    vector<int> a(n), ans(q);
    // store queries in the form qry[l] = {r, index of query}
    vector<vector<pair<int, int>>> qry(n);
    for (auto &x : a)
        cin >> x;
    for (int i = 0; i < q; i++)
    {
        int l, r;
        cin >> l >> r;
        l--, r--;
        qry[l].push_back({r, i});
    }
    // make a special segment tree
    Segment st(a);
    // push infinite value for stable stack
    a.push_back(1e9);
    // h will store prefix contribution sum and s will store the indices for next greater element
    vector<int> s, h;
    s.push_back(n), h.push_back(0);
    vector<int> contri(n + 1);
    // cur will store current weight of contributions
    int cur = 0;
    for (int i = n - 1; i >= 0; i--)
    {
        while (a[s.back()] < a[i])
            cur -= contri[s.back()],
                s.pop_back(), h.pop_back();
        contri[i] = a[i] * (s.back() - i);
        cur += contri[i];
        // just do what you do to make next greater element and add prefix of contributions as well
        s.push_back(i), h.push_back(contri[i] + h.back());
        for (auto [r, ii] : qry[i])
        {
            // now first index that has next greater element beyond r, this overlaps with range [r + 1, n - 1]
            int idx = upper_bound(s.rbegin(), s.rend(), r) - 1 - s.rbegin();
            int x = *(s.rbegin() + idx);
            // contribution[l, r] = contribution[l, n - 1] - contribution[m, n - 1] + contribution[m, r]
            // this is contribution[l, n - 1]
            int res = cur;
            // this is contribution of [m, n - 1]
            res -= *(h.rbegin() + idx);
            // this is contribution of [m, r]
            res += a[x] * (r - x + 1);
            // answer should be contribution[l, r] - sum[l, r]
            res -= st.sum(i, r);
            ans[ii] = res;
        }
    }
    for (auto x : ans)
        cout << x << endl;
}
