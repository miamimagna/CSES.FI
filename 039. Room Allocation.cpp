#include <cstdio>
#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <utility>
#include <set>
#include <queue>
// #define int long long
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
    int n, cnnnt = -1;
    cin >> n;
    v<tuple<int, int, int>> a(n);
    for(auto &[x, y, z]: a)
        z = ++cnnnt, cin >> x >> y;
    sortv(a);
    priority_queue<pair<int, int>> q;
    v<int> ans(n);
    int mx = 0;
    for(auto &[start, end, index]: a){
        if(q.empty()) {
            ans[index] = ++mx;
            q.emplace(-end, mx);
        }
        else {
            auto [min_prev_end, room_no] = q.top();
            // cout << min_prev_end << ' ' << room_no << ' ' << start << ' ' << end << ' ' << index << endl;
            if(-min_prev_end < start){
                q.pop();
                ans[index] = room_no;
                q.emplace(-end, room_no);
            }
            else {
                ans[index] = ++mx;
                q.emplace(-end, mx);
            }
        }
    }
    cout << mx << endl;
    for(auto x: ans) 
        cout << x << ' '; 
    cout << endl; 
}
signed main()
{
    solve();
}
