#include <iostream>
#include <cstdio>
#include <vector>
#include <algorithm>
#include <cstring>
using namespace std;
struct Query
{
    int l, r, i;
    Query() = default;
    Query(int l, int r, int i) : l(l), r(r), i(i) {}
};
struct Ele
{
    int val, i, ri;
};
Query queries[(size_t)2e5];
Ele a[(size_t)2e5];
int freq[(size_t)2e5];
int first, last, cur;
void move(int aa, int b)
{
    while (aa < first)
    {
        first--;
        if (++freq[a[first].i] == 1)
            cur++;
    }
    while (last < b)
    {
        last++;
        if (++freq[a[last].i] == 1)
            cur++;
    }
    while (first < aa)
    {
        if (--freq[a[first].i] == 0)
            cur--;
        first++;
    }
    while (b < last)
    {
        if (--freq[a[last].i] == 0)
            cur--;
        last--;
    }
}
#include <cmath>
signed main()
{
#ifdef LOCAL
    freopen("input.txt", "r", stdin);
#endif
    ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);
    int n, q, blsize = 600;
    cin >> n >> q;
    for (int i = 0; i < n; i++)
        cin >> a[i].val, a[i].ri = i;
    {
        sort(a, a + n, [](const Ele &a, const Ele &b)
             { return a.val < b.val; });
        a[0].i = 0;
        for (int i = 1; i < n; i++)
            a[i].i = a[i - 1].i + (a[i].val != a[i - 1].val);
        sort(a, a + n, [](const Ele &a, const Ele &b)
             { return a.ri < b.ri; });
    }
    memset(freq, 0, sizeof(freq));
    for (int i = 0; i < q; i++)
    {
        cin >> queries[i].l >> queries[i].r;
        queries[i].i = i;
    }
    sort(queries, queries + q, [&](const Query &a, const Query &b)
         {
        if(a.l / blsize == b.l / blsize)
            return a.r < b.r;
        return a.l < b.l; });
    vector<int> ans(q);
    cur = 0, first = 0, last = -1;
    for (int i = 0; i < q; i++)
    {
        int l = queries[i].l - 1, r = queries[i].r - 1;
        move(l, r);
        ans[queries[i].i] = cur;
    }
    for (auto x : ans)
        printf("%d \n", x);
}
