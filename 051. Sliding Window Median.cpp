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
#define sz size() 
#define pb push_back 
void solve()
{
    int n, k; 
    cin >> n >> k;
    v<int> a(n);
    for(auto &x: a) 
        cin >> x;
    multiset<int> low, hi;
    for(int i = 0; i < k; i++){
        low.insert(a[i]);
        if(low.sz > (k + 1) / 2)
            hi.insert(*low.rbegin()), low.erase(low.find(*low.rbegin()));
    }
    v<int> ans{*low.rbegin()};
    for(int i = k; i < n; i++){
        low.insert(a[i]);
        if(low.sz > (k + 1) / 2)
            hi.insert(*low.rbegin()), low.erase(low.find(*low.rbegin()));
        int er = a[i - k];
        if(er > *low.rbegin()){
            hi.erase(hi.find(er));
        }
        else {
            low.erase(low.find(er));
            low.insert(*hi.begin()), hi.erase(hi.begin());
        }
        ans.pb(*low.rbegin());
    }
    for(auto x: ans) cout << x << ' '; cout << endl;
}
signed main()
{
    solve();
}
