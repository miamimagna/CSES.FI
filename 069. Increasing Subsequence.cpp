#include <cstdio>
#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
using namespace std;
// preprocessing to make code easier
template <typename T>
using v = vector<T>;
#define sz size()
#define int long long
int mod = 1e9 + 7;
int lengthOfLIS(vector<int> &a)
{
    vector<int> dp = {(int)-1e18};
    for (const int x : a)
        if (x > dp.back())
            dp.push_back(x);
        else
            *lower_bound(dp.begin(), dp.end(), x) = x;
    return dp.size() - 1;
}
void solve(){
    int n; 
    cin >> n;
    v<int> a(n);
    for(auto &x: a) cin >> x;
    cout << lengthOfLIS(a) << endl;
}
signed main()
{
    solve();
}
