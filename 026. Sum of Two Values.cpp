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
    int n, __cnt = 0, target; 
    cin >> n >> target;
    v<pair<int, int>> a(n);
    for(auto &[x, y]: a)
        cin >> x, y = ++__cnt;
    sortv(a);
    int hi = n - 1, lo = 0;
    while(hi > lo){
        int sum = a[hi].first + a[lo].first;
        if(sum == target){
            cout << a[lo].second << ' ' << a[hi].second << endl;
            return;
        }
        else if(sum > target) hi--;
        else lo++;
    }
    cout << "IMPOSSIBLE" << endl;
}
signed main()
{
    solve();
}
