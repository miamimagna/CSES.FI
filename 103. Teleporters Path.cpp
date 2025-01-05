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
/*
//this code runs at 0.06s, which is 50 times faster than above code but it needs high level thinking
#include <cstdio>
#include <vector>
using namespace std;
template <typename t>
using v = vector<t>;
const int N = 1e5 + 1;
static int st[2 * N];
static v<int> adj[N];
// we will simulate stack using two variable top and restop on st and res respectively
static int top = -1, restop = -1;
static int res[2 * N];
#ifdef LOCAL
#define putchar_unlocked _putchar_nolock
#define getchar_unlocked _getchar_nolock
#endif
// getint and putint are faster version of cin and cout
static inline int getint()
{
    int x, y;
    while ((x = getchar_unlocked()) < '0')
    {
    }
    x -= '0';
    while ((y = getchar_unlocked()) >= '0')
    {
        x = x * 10 + y - '0';
    }
    return x;
}
static inline void putint(int x)
{
    char s[10];
    short i = 0;
    if (x == 0)
    {
        putchar_unlocked('0');
        return;
    }
    while (x)
    {
        s[i++] = (x % 10) + '0';
        x /= 10;
    }
    while (i--)
    {
        putchar_unlocked(s[i]);
    }
}
int main()
{
// so indeg array is unnecessary as we only need value of indeg[1] and indeg[n], so we will store indeg[x] - outdeg[x] in first and second for 1 and n
// we know that for values between 2 and n - 1, indeg should be equal to outdeg, we can reduce the array usage by storing this info in single int
// using addition and subtraction of edges
    static int n = getint(), m = getint(), cnt = 0, first = 0, second = 0, x, y;
    for (int i = 0; i < m; i++)
        x = getint(), y = getint(),
        // trust me it is same as above code just for 1 and n
        first += (y == 1) - (x == 1),
        second += (y == n) - (x == n),
        cnt += y, cnt -= x,
        adj[x].push_back(y);
    // now hierholzer algorithm stack version
    st[++top] = 1;
    while (top != -1)
    {
        int x = st[top];
        if (adj[x].size())
            adj[x].pop_back(),
                st[++top] = adj[x].back(),
                m--;
        else
            res[++restop] = x, top--;
    }
    // hierholzer(1);
    // you can notice we have reduced number of if statements
    // now here is the magic, second and first are trivial
    if (cnt != n - 1 || second != 1 || first != -1 || m)
        puts("IMPOSSIBLE");
    else
        while (restop != -1)
            putint(res[restop--]), putchar_unlocked(' ');
    putchar_unlocked('\n');
}
*/
