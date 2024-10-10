#include <iostream>
#include <vector>
#include <cstdint>
#define int long long
int32_t main()
{
    int n;
    std::cin >> n;
    if (n == 1)
    {
        std::cout << n << std::endl;
        return 0;
    }
    if (n < 4)
        std::cout << "NO SOLUTION" << std::endl;
    else
    {
        int x = 2;
        for (; x <= n; x += 2)
            std::cout << x << " ";
        x = 1;
        for (; x <= n; x += 2)
            std::cout << x << " ";
    }
    std::cout << std::endl;
}
