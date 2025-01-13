#include <cmath>
#include <iostream>
#include <algorithm>
#include <vector>
#include <unordered_map>
#include <string>
#include <set>
#include <unordered_set>
using namespace std;
// preprocessing to make code easier
#define int long long
template <typename T>
using v = vector<T>;
int n = 8;
v<v<int>> board(n, v<int>(n, -1));
v<v<bool>> vis(n, v<bool>(n));
v<int> dx = {-2, -2, 2, 2, -1, -1, 1, 1};
v<int> dy = {-1, 1, -1, 1, 2, -2, 2, -2};
bool isValid(int x, int y)
{
    return x >= 0 && y >= 0 && x < n && y < n && !vis[x][y];
}
int deg(int x, int y)
{
    int cnt = 0;
    for (int i = 0; i < 8; i++)
        cnt += isValid(x + dx[i], y + dy[i]);
    return cnt;
}
bool dfs(int x, int y, int move = 1)
{
    board[x][y] = move;
    vis[x][y] = 1;
    if (move == 64)
        return true;
    v<tuple<int, int, int>> a;
    for (int i = 0; i < 8; i++)
    {
        int xx = x + dx[i], yy = y + dy[i];
        if (!isValid(xx, yy))
            continue;
        a.push_back({deg(xx, yy), xx, yy});
    }
    sort(a.begin(), a.end());
    for (auto [a, xx, yy] : a)
        if (dfs(xx, yy, move + 1))
            return true;
    board[x][y] = 0, vis[x][y] = 0;
    return false;
}
signed main()
{
#ifdef LOCAL
    freopen("input.txt", "r", stdin);
    // freopen("output.txt", "w", stdout);
#else
    ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);
#endif
    int x, y;
    cin >> x >> y;
    x--, y--;
    dfs(y, x);
    for (auto x : board)
    {
        for (auto y : x)
            cout << y << ' ';
        cout << endl;
    }
}
