#include <iostream>
#include <cstdint>
#define int long long
int32_t main()
{
    int n;
    std::cin >> n;
    std::cout << n << " ";
    while (n != 1)
    {
        if (n % 2)
        {
            n *= 3;
            std::cout << ++n << " ";
        }
        else
        {
            n /= 2;
            std::cout << n << " ";
        }
    }
    std::cout << std::endl;
}
