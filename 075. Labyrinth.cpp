#include <cstdio>
#include <iostream>
#include <vector>
#include <string>
#include <utility>
#include <queue>
#include <algorithm>
using namespace std;
// preprocessing to make code easier
template <typename T>
using v = vector<T>;
#define sz size()
#define int long long
int mod = 1e9 + 7;
int n, m;
void bfs(int sr, int sc, v<string> &a){
    v<v<int>> mn(n, v<int>(m, 1e9));
    v<int> dirx = {1, -1, 0, 0}, diry = {0, 0, 1, -1};
    string moves = "UDLR";
    queue<pair<int, int>> q;
    q.emplace(sr, sc);
    mn[sr][sc] = 0;
    int minMoves = 1e9;
    pair<int, int> dest;
    while(q.sz){
        auto [i, j] = q.front();
        q.pop();
        if(a[i][j] == 'B') {
            dest = {i, j};
            minMoves = mn[i][j];
            break;
        }
        for(int k = 0; k < 4; k++){
            int x = i + dirx[k], y = j + diry[k];
            if(x < n && y < m && x >= 0 && y >= 0 && a[x][y] != '#' && mn[x][y] > mn[i][j] + 1){
                mn[x][y] = mn[i][j] + 1;
                q.emplace(x, y);
            }
        }
    }
    if(minMoves != 1e9){
        cout << "YES" << endl;
        cout << minMoves << endl;
        string ans;
        while(minMoves--){
            for (int k = 0; k < 4; k++)
            {
                int x = dest.first + dirx[k], y = dest.second + diry[k];
                if (x < n && y < m && x >= 0 && y >= 0 && a[x][y] != '#' && mn[x][y] == mn[dest.first][dest.second] - 1)
                {
                    ans += moves[k];
                    dest = {x, y};
                    break;
                }
            }
        }
        reverse(ans.begin(), ans.end());
        cout << ans << endl;
    }
    else cout << "NO" << endl;
}
void solve(){
    cin >> n >> m;
    v<string> a(n);
    for(auto &x: a) cin >> x;
    pair<int, int> start;
    for(int i = 0; i < n; i++)
        for(int j = 0; j < m; j++)
            if(a[i][j] == 'A') start = {i, j};
    bfs(start.first, start.second, a);
}
signed main()
{
#ifdef LOCAL
    freopen("input.txt", "r", stdin);
#endif
    solve();
}
