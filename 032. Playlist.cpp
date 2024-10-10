#include <iostream>
#include <vector>
#include <string>
#include <unordered_map>
#include <algorithm>
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
    int n; 
    cin >> n;
    v<int> a(n);
    for(auto &x: a) cin>>x;
    unordered_map<int, int> mp(2e5);
    int cur=0, ans = 1;
    for(int i = 0; i < n; i++){
        if(mp.count(a[i])){
            int j = mp[a[i]];
            cur = min(i - j, cur + 1);
            ans = max(ans, cur);
        }
        else cur++, ans = max(ans, cur);
        mp[a[i]] = i;
        // cout<<ans << ' ' << cur << endl;
    }
    cout<<ans<<endl;
}
signed main()
{
    solve();
}
