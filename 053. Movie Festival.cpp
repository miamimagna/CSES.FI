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
#define sortv(a) sort(a.begin(), a.end()) 
void solve()
{
    int n, k;
    cin >> n >> k;
    v<pair<int, int>> a(n);
    for(auto &[end, start]: a)
        cin >> start >> end;
    sortv(a);
    multiset<int> s;
    int ans = 0;
    for(auto &[end, start]: a){
        if(!s.sz)
            ans++, s.insert(end);
        else if(*s.begin() <= start)
            s.erase(--s.upper_bound(start)), ans++, s.insert(end);
        else if(s.sz < k)
            ans++, s.insert(end);
    }
    cout << ans << endl;
}
signed main()
{
    solve();
}
