#include <bits/stdc++.h>
#define int long long
#define endl '\n'
using namespace std;
vector<int> nums(18, 0);
int spow(int n, int m)
{
    if (m == 0)
    {
        return 1;
    }
    return spow(n, m / 2) * spow(n, m / 2) * (m % 2 ? n : 1);
}
void solve()
{
    int number;
    cin >> number;
    int digits_num = (lower_bound(nums.begin(), nums.end(), number) - nums.begin());
    number -= nums[digits_num - 1];
    int initial_num{(spow(10, digits_num - 1))};
    int req_num = initial_num + bool(number % (int)digits_num) + (number / digits_num) - 1;
    int mod = number - 1;
    mod %= (int)digits_num;
    string s;
    s = to_string(req_num);
    cout << s[mod] << endl;
    return;
}
signed main()
{
    for (int i = 1; i < 18; i++)
        nums[i] = i * 9 * spow(10, i - 1) + nums[i - 1];

    int q;
    cin >> q;
    while (q--)
        solve();
}
