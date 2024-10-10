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
#define ff first 
#define ss second
int mod = 1e9 + 7;
int dirx[] = {1, -1, 0, 0}, diry[] = {0, 0, 1, -1};
string moves = "DURL";
bool found = false;
string cur, ans;
void dfs(int row, int col, v<string>& a, v<v<int>> &mndanger, int n, int m, int depth = 0){
    if(a[row][col] == '#' || a[row][col] == 'M' || depth >= mndanger[row][col] || found) return;
    if(row == 0 || col == 0 || row == n - 1 || col == m - 1) {
        found = true;
        ans = cur;
        return;
    }
    mndanger[row][col] = depth;
    for(int i = 0; i < 4; i++){
        int x = row + dirx[i], y = col + diry[i];
        char ch = moves[i];
        cur.push_back(ch);
        dfs(x, y, a, mndanger, n, m, depth + 1);
        cur.pop_back();
    }
}
void solve(){
    int m, n;
    cin >> n >> m;
    v<string> a(n);
    queue<pair<int, int>> q;
    v<v<int>> mndanger(n, v<int>(m, 1e9));
    pair<int, int> start;
    for(auto &x: a) cin >> x;
    for(int i = 0; i < n; i++)
        for(int j = 0; j < m; j++)
            if(a[i][j] == 'M') q.emplace(i, j), mndanger[i][j] = 0;
            else if(a[i][j] == 'A') start = {i, j};
    // do bfs from each monster to get their minimum reachability
    while(q.sz){
        auto [row, col] = q.front(); q.pop();
        for(int i = 0; i < 4; i++){
            int x = row + dirx[i], y = col + diry[i];
            if(x >= 0 && x < n && y >= 0 && y < m && a[x][y] != '#')
                if(mndanger[x][y] > mndanger[row][col] + 1)
                    mndanger[x][y] = mndanger[row][col] + 1,
                    q.emplace(x, y);
        }
    }
    // now do dfs for our hero
    dfs(start.ff, start.ss, a, mndanger, n, m);
    if(found){
        cout << "YES" << endl;
        cout << ans.sz << endl;
        cout << ans << endl;
    }
    else cout << "NO" << endl;
}
signed main()
{
#ifdef LOCAL
    freopen("input.txt", "r", stdin);
#endif
    solve();
}
