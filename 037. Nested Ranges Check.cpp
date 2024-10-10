#include <cstdio>
#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <utility>
#include <set>
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
    int n; cin>>n;
    v<pair<int, int>> a(n);
    for(auto &[x, y]: a) 
        cin >> x >> y;
    v<tuple<int, int, int>> b;
    for(auto [x, y]: a)
        b.eb(x, -y, b.size());
    sortv(b);
    v<int> contained(n);
    int mn = 1e9;
    for(auto [x, y, z]: b){
        if(mn <= y) contained[z] = 1;
        mn = min(mn, y);
    }
    reverse(each(b));
    int mx = -1e9 - 1;
    v<int> contains(n);
    for(auto [x, y, z]: b){
        if(mx >= y) contains[z] = 1;
        mx = max(mx, y);
    }
    for(auto x: contains)
        cout << x << ' '; 
    cout << endl;
    for(auto x: contained)
        cout << x << ' ';
    cout << endl;
}
signed main()
{
    solve();
}
