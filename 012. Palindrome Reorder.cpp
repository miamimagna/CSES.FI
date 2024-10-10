#include <iostream>
#include <vector>
#include <cstdint>
#include <utility>
#include <string>
#define int long long
using namespace std;
void solve()
{
    string s;
    cin >> s;
    int a[26] = {};
    for (auto c : s)
        a[c - 'A']++;
    char center = '#';
    string ans(s.size(), '#');
    int l = 0, r = s.size() - 1;
    for (int i = 0; i < 26; i++)
    {
        if (a[i] % 2)
        {
            if (center == '#')
                center = i + 'A', ans[s.size() / 2] = center;
            else
                center = 'a';
            a[i] --;
        }
        while(a[i] > 0)
            ans[l++] = i + 'A', ans[r--] = i + 'A', a[i] -= 2;
    }
    if(center == 'a') cout << "NO SOLUTION" << endl;
    else cout << ans;
}
signed main()
{
    solve();
}
