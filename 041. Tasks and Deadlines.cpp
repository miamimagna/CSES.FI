#include <cstdio>
#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <utility>
#include <set>
#include <queue>
#define int long long
using namespace std;
// preprocessing to make code easier
template <typename T>
using v = vector<T>;
#define maxheap(T) priority_queue<T>
#define minheap(T) priority_queue<T, v<T>, greater<T>>
#define heap(T, comp) priority_queue<T, v<T>, comp>
#define ff first
#define ss second
#define sz size()
#define pb push_back
#define eb emplace_back
#define sortc(a, comp) sort(a.begin(), a.end(), comp)
#define sortv(a) sort(a.begin(), a.end())
#define each(a) a.begin(), a.end()
#define lb lower_bound
#define ub upper_bound
void solve()
{
    int n; 
    cin >> n;
    v<pair<int, int>> a(n);
    for(auto &[x, y]: a) 
        cin >> x >> y;
    sortv(a);
    int cur = 0, reward = 0;
    for(auto [x, y]: a)
        cur += x, 
        reward += y - cur;
    cout << reward << endl;
}
signed main()
{
    solve();
}
