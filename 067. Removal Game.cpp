#include <cstdio>
#include <iostream>
#include <vector>
#include <string>
using namespace std;
// preprocessing to make code easier
template <typename T>
using v = vector<T>;
#define sz size()
#define int long long
int mod = 1e9 + 7;
// default value of dp
pair<int, int> def = {-1e18, -1e18};
// memoization
pair<int, int> generate(bool turn, int l, int r, v<int> &a, v<v<pair<int, int>>> &dp)
{
    if (l == r)
    {
        if (turn)
            return {0, a[l]};
        else
            return {a[l], 0};
    }
    if (dp[l][r] != def)
        return dp[l][r];
    // take front element
    auto front = generate(!turn, l + 1, r, a, dp);
    // take end first
    auto end = generate(!turn, l, r - 1, a, dp);
    if (turn)
    {
        if (front.first - front.second - a[l] < end.first - end.second - a[r])
            return dp[l][r] = {front.first, front.second + a[l]};
        else
            return dp[l][r] = {end.first, end.second + a[r]};
    }
    else
    {
        if (front.second - front.first - a[l] < end.second - end.first - a[r])
            return dp[l][r] = {front.first + a[l], front.second};
        else
            return dp[l][r] = {end.first + a[r], end.second};
    }
}
// tabulation
pair<int, int> generate_tabu(v<int> &a, v<v<pair<int, int>>> &dp){
    int n = dp.sz;
    bool turn = n % 2;
    for(int i = 0; i < n; i++)
        if(turn) dp[i][i] = {a[i], 0};
        else dp[i][i] = {0, a[i]};
    for(int j = 1; j < n; j++)
        for(int i = 0; i + j < n; i++){
            int l = i, r = i + j;
            turn = (r - l + 1) % 2;
            auto front = dp[l + 1][r];
            auto end = dp[l][r - 1];
            if (turn ^ n % 2)
            {
                if (front.first - front.second - a[l] < end.first - end.second - a[r])
                    dp[l][r] = {front.first, front.second + a[l]};
                else
                    dp[l][r] = {end.first, end.second + a[r]};
            }
            else
            {
                if (front.second - front.first - a[l] < end.second - end.first - a[r])
                    dp[l][r] = {front.first + a[l], front.second};
                else
                    dp[l][r] = {end.first + a[r], end.second};
            }
        }
    return dp[0][n - 1];
}
void solve()
{
    int n;
    cin >> n;
    v<int> a(n);
    for (auto &x : a)
        cin >> x;
    v<v<pair<int, int>>> dp(n, v<pair<int, int>>(n, {-1e18, -1e18}));
    cout << generate_tabu(a, dp).first << endl;
}
signed main()
{
    solve();
}
