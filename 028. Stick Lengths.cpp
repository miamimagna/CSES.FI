#include <iostream>
#include <algorithm>
#include <vector>
#define endl '\n'
#define pc putchar_unlocked
int main()
{
    int n;
    std::cin >> n;
    std::vector<int> a(n);
    for (int i = 0; i < n; i++)
    {
        std::cin >> a[i];
    }
    std::sort(a.begin(), a.end());
    long long sum{};
    int mid = n / 2;
    for (int i = 0; i < mid; i++)
    {
        sum += a[mid] - a[i];
    }
    for (int i = mid + 1; i < n; i++)
    {
        sum += a[i] - a[mid];
    }
    std::cout << sum << endl;
}
