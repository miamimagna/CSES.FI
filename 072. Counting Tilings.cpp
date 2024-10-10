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
#define int long long
int mod = 1e9 + 7;
int n, m;
/*
this is bruteforce approach just for reference
// dp is of the form dp[n][m][mask][horizontal_continue]
int dp[1000][10][1 << 10][2];
int generate(int i, int j, int mask, bool hcon){
    // go to next line if at end
    if(j == m) return generate(i + 1, 0, mask, 0);
    // if at last line's end, return 1 only if no board is incomplete
    if(i == n) return mask == 0;
    // memoized answer returned
    if(dp[i][j][mask][hcon] != -2) return dp[i][j][mask][hcon];
    // vertical continuation boolean for ongoing vertical board
    bool vcon = mask & (1 << j);
    // we can't have both vertical and horizontal board in continuity
    if(vcon && hcon) return 0;
    // missingCol is the mask with no vertical board continue at j index
    int missingCol = vcon? mask - (1 << j) : mask;
    // continue horizontal board
    if(hcon) return generate(i, j + 1, missingCol, 0);
    // continue vertical board
    if(vcon) return generate(i, j + 1, missingCol, 0);
    dp[i][j][mask][hcon] = 0;
    // start a new horizontal board
    if(j != m - 1) dp[i][j][mask][hcon] += generate(i, j + 1, missingCol, 1);
    // start a new vertical board
    if(i != n - 1) dp[i][j][mask][hcon] += generate(i, j + 1, missingCol + (1 << j), 0);
    return dp[i][j][mask][hcon] % mod;
}
void solve(){
    cin >> m >> n;
    // initialize array
    for(int i = 0; i < 1000; i++)
        for(int j = 0; j < 10; j++)
            for(int k = 0; k < (1 << 10); k++)
                for(int l = 0; l < 2; l++)
                    dp[i][j][k][l] = -2;
    cout << generate(0, 0, 0, 0) << endl;
}
 */
void generateMasks(int i, int mask, v<int>& nextMasks, int j = 0, int cur = 0){
    if(j == m) nextMasks.push_back(cur);
    else {
        int vcon = mask & (1 << j);
        int nextvcon = mask & (1 << (j + 1));
        // continue vertical board
        if(vcon) {
            generateMasks(i, mask, nextMasks, j + 1, cur);
            return;
        }
        // start a new horizontal board
        if(j != m - 1 && !nextvcon) generateMasks(i, mask, nextMasks, j + 2, cur);
        // start a new vertical board
        if(i != n - 1){
            cur += (1 << j);
            generateMasks(i, mask, nextMasks, j + 1, cur);
        }
    }
}
int countTile(int i, int mask, v<v<int>> &dp)
{
    if (i == n)
        return mask == 0;
    // if already computer answer just return stored answer
    if (dp[i][mask] != -1)
        return dp[i][mask];
    dp[i][mask] = 0;
    // this array will contain all possible masks that are possible for ith row if (i - 1)th row had mask configuration
    v<int> nextMasks;
    generateMasks(i, mask, nextMasks);
    // for every possible mask, generate solution
    for(auto x: nextMasks){
        dp[i][mask] = (dp[i][mask] + countTile(i + 1, x, dp)) % mod;
    }
    // return answer
    return dp[i][mask];
}
// tabulation of same approach as above(also space optimized)
int countTile_Tabu(){
    v<int> dp(1 << m), prev = dp, temp = dp;
    // base case would be last row
    prev[0] = 1;
    // for every row, at the end of loop, dp should become prev and a new empty array should be in place of dp
    for(int i = n - 1; i >= 0; i--, prev = dp, dp = temp)
    // for every mask value, generate answers
        for(int mask = 0; mask < (1 << m); mask++){
            v<int> nextMasks;
            generateMasks(i, mask, nextMasks);
            for(auto x: nextMasks)
                dp[mask] = (dp[mask] + prev[x]) % mod;
        }
    // return the answer for 0 configuration at start
    return prev[0];
}
void solve()
{
    cin >> m >> n;
    // v<v<int>> dp(n, v<int>((1 << m), -1)); this is needed in case of memoization
    cout << countTile_Tabu() << endl;
}
signed main()
{
    solve();
}
