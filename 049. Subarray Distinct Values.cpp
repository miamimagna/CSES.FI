#include <cstdio>
#include <iostream>
#include <vector>
#include <algorithm>
#include <utility>
#include <unordered_map>
#define int long long
using namespace std;
// preprocessing to make code easier 
template <typename T> 
using v = vector<T>; 
#define sz size() 
void solve()
{
    int n, ans = 0, k; 
    cin >> n >> k;
    v<int> a(n);
    for(auto &x: a) 
        cin >> x;
    int l = 0;
    unordered_map<int, int> mp;
    for(int r = 0; r < n; r++){
        mp[a[r]]++;
        while(mp.sz > k){
            mp[a[l]]--;
            if(!mp[a[l]]) mp.erase(a[l]);
            l++;
        }
        int num = r - l + 1;
        ans += num;
    }
    cout << ans << endl;
}
signed main()
{
    solve();
}
