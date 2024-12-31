#include <cstdio>
#include <vector>
#include <cmath>
using namespace std;
template <class t>
using v = vector<t>;
#define int long long
int up[200000][30];
// I knew how to do it still it took an hour or so just becuase of (1ll << i) instead of (1 << i) giving overflow
int query(int u, int k)
{
    if (!k)
        return u;
    for (int i = ceil(log2(k)); i >= 0; i--)
        if ((1ll << i) < k)
            u = up[u][i], k -= (1ll << i);
    return up[u][0];
}
signed main()
{
#ifdef LOCAL
    freopen("input.txt", "r", stdin);
#endif
    int n, q;
    scanf("%lld %lld", &n, &q);
    for (int i = 1; i <= n; i++)
    {
        int x;
        scanf("%lld ", &x);
        up[i][0] = x;
    }
    for (int i = 1; i < 30; i++)
        for (int j = 1; j <= n; j++)
            up[j][i] = up[up[j][i - 1]][i - 1];
    while (q--)
    {
        int u, k;
        scanf("%lld %lld", &u, &k);
        printf("%lld \n", query(u, k));
    }
    return 0;
}
