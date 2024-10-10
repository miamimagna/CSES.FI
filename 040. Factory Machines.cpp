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
bool isPossible(v<int> &a, int total, int x){
    int cnt = 0;
    for(auto time: a){
        cnt += x / time;
        if(cnt >= total) return true;
    }
    return false;
}
void solve()
{
    int n, total;
    cin >> n >> total;
    v<int> a(n);
    for(auto &x: a) 
        cin >> x;
    int hi = 1e18, lo = 1;
    int ans = -1;
    while(hi >= lo){
        int mid = (hi + lo) >> 1;
        if(isPossible(a, total, mid)) ans = mid, hi = mid - 1;
        else lo = mid + 1;
    }
    cout << ans << endl;
}
signed main()
{
    solve();
}
