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
    int n; cin>>n;
    v<int> a(n);
    for(auto &x: a) cin>>x;
    sortv(a);
    int sum = 0, ans = -1;
    for(auto x: a)
        if(sum + 1 < x){
            ans = sum + 1;
            break;
        }
        else sum += x;
    if(ans == -1) ans = sum + 1;
    cout<<ans<<endl;
}
signed main()
{
    solve();
}
