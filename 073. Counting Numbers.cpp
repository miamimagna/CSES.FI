#include <cstdio>
#include <iostream>
#include <vector>
#include <string>
#include <utility>
#include <algorithm>
using namespace std;
// preprocessing to make code easier
template <typename T>
using v = vector<T>;
#define sz size()
#define int long long
int mod = 1e9 + 7;
// structure here denotes as follows:
// i = current index, prev = previous digit, up = upper bounded current value(that is value is going same as upper bound
// low = lower bound current value, leading zero = leading zeroes in current value
int solveHelper(string& a, string& b, v<v<v<v<int>>>>& dp, int i, int prev, bool up, bool low, bool leadingZero = 1){
    if(i == b.sz) return 1;
    int &res = dp[up][low][i][prev];
    if(res != -1) return res;
    res = 0;
    int mn = low? a[i] - '0': 0;
    int mx = up? b[i] - '0': 9;
    for(int ch = mn; ch <= mx; ch++)
        if(prev != ch || ch == 0 && leadingZero)
            res += solveHelper(a, b, dp, i + 1, ch, up && (ch == b[i] - '0'), low && (ch == a[i] - '0'), leadingZero && (ch == 0));
    return res;
}
void solve()
{
    int a, b;
    cin >> a >> b;
    string sb = to_string(b), sa = to_string(a);
    int dif = sb.sz - sa.sz;
    string saa;
    while(dif--)
        saa.push_back('0');
    saa = saa + sa;
    v<v<v<v<int>>>> dp(2, v<v<v<int>>>(2, v<v<int>>(sb.sz, v<int>(11, -1))));
    cout << solveHelper(saa, sb, dp, 0, 10, 1, 1) << endl;
}
signed main()
{
#ifdef LOCAL
    freopen("input.txt", "r", stdin);
#endif
    solve();
}
