#include <iostream>
#include <vector>
#include <string>
#include <unordered_set>
#include <algorithm>
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
    int n, x;
    cin>>n>>x;
    v<int> a(n);
    for(auto &x: a) cin>>x;
    sortv(a);
    int l = 0, r = n - 1, cnt = 0;
    while(l <= r){
        if(l != r && a[l] + a[r] <= x) l++;
        cnt++, r--;
    }
    cout<<cnt<<endl;
}
signed main()
{
    solve();
}
