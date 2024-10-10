#include <iostream>
#include <algorithm>
#include <vector>
#define endl '\n'
#define pc putchar_unlocked
 
int main()
{
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(0);
    int n, i{};
    long long cur_sum{}, max_sum{-1000000001};
    std::cin >> n;
    std::vector<int> a(n);
    for (int i = 0; i < n; i++)
    {
        std::cin >> a[i];
    }
    while (i < n)
    {
        cur_sum += a[i++];
        if (max_sum < cur_sum)
            max_sum = cur_sum;
        if (cur_sum < 0)
            cur_sum = 0;
    }
    std::cout << max_sum << endl;
}
