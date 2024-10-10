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
void solve(){
    int n, m;
    cin >> n >> m;
    v<v<int>> adj(n + 1);
    while(m--){
        int x, y;
        cin >> x >> y;
        adj[x].push_back(y), adj[y].push_back(x);
    }
    int first = 0, possible = 1;
    v<int> ans(n + 1, -1);
    for(int i = 1; i <= n; i++)
        if(ans[i] == -1){
            // fill all elements starting from here
            queue<int> q;
            q.push(i);
            ans[i] = first;
            first = !first;
            while(q.sz && possible){
                int cur = q.front(); q.pop();
                for(int x: adj[cur])
                    if(ans[x] == ans[cur]){
                        possible = false;
                        break;
                    }
                    else if(ans[x] == -1)
                        ans[x] = !ans[cur], q.push(x);
            }
        }
    if(possible)
        for(int i = 1; i <= n; i++)
            cout << ans[i] + 1 << ' ';
    else cout << "IMPOSSIBLE";
    cout << endl;
}
signed main()
{
#ifdef LOCAL
    freopen("input.txt", "r", stdin);
#endif
    solve();
}
