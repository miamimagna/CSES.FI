#include <cstdio>
#include <iostream>
#include <vector>
#include <algorithm>
#include <utility>
#include <set>
#define int long long
using namespace std;
// preprocessing to make code easier 
template <typename T> 
using v = vector<T>; 
#define ff first 
#define ss second 
#define sz size() 
#define pb push_back 
#define eb emplace_back 
#define sortv(a) sort(a.begin(), a.end()) 
void solve()
{
    int n, k; 
    cin >> n >> k;
    v<int> a(n);
    for(auto &x: a) 
        cin >> x;
    multiset<int> low, hi;
    int lowsum = 0, hisum = 0;
    for(int i = 0; i < k; i++){
        low.insert(a[i]);
        lowsum += a[i];
        if(low.sz > (k + 1) / 2)
            lowsum -= *low.rbegin(), hisum += *low.rbegin(),
            hi.insert(*low.rbegin()), low.erase(low.find(*low.rbegin()));
    }
    int lowend = *low.rbegin(), res = (lowend * low.size() - lowsum) + (hisum - lowend * hi.size());
    v<int> ans{res};
    for(int i = k; i < n; i++){
        low.insert(a[i]);
        lowsum += a[i];
        if(low.sz > (k + 1) / 2)
            lowsum -= *low.rbegin(), hisum += *low.rbegin(),
            hi.insert(*low.rbegin()), low.erase(low.find(*low.rbegin()));
        int er = a[i - k];
        if(er > *low.rbegin()){
            hisum -= er;
            hi.erase(hi.find(er));
        }
        else {
            low.erase(low.find(er));
            lowsum -= er;
            lowsum += *hi.begin(), hisum -= *hi.begin();
            low.insert(*hi.begin()), hi.erase(hi.begin());
        }
        int lowend = *low.rbegin(), res = (lowend * low.size() - lowsum) + (hisum - lowend * hi.size());
        ans.pb(res);
    }
    for(auto x: ans) cout << x << ' '; cout << endl;
}
signed main()
{
    solve();
}
