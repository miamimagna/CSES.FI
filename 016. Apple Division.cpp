#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
#include <climits>
#define int long long
#define endl '\n'
#define FIO                           \
    std::ios::sync_with_stdio(false); \
    std::cin.tie(0);                  \
    std::cin.tie(0);
signed main()
{
    FIO;
    int n;
    std::cin >> n;
    std::vector<int> a(n);
    double sum{};
    for (auto &x : a)
    {
        std::cin >> x;
        sum += x;
    }
    int minn{INT_MAX};
    for (int i = 0; i < std::pow(2, n); i++) // we can also use 1<<2
    {
        int s{};
        for (int j = 0; j < n; j++)
        {
            if (i & 1 << j)
                s += a[j];
        }
        int current_sum = (std::abs((sum - s) - s));
        minn = std::min(minn, current_sum);
    }
    std::cout << minn << endl;
}
