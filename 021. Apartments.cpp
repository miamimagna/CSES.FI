#include <iostream>
#include <vector>
#include <algorithm>
#define int long long
#define endl '\n'
signed main()
{
    FIO;
    int n, m, k;
    std::cin >> n >> m >> k;
    std::vector<int> customer(n);
    std::vector<int> apartments(m);
    for (auto &x : customer)
        std::cin >> x;
    for (auto &x : apartments)
        std::cin >> x;
 
    std::sort(customer.begin(), customer.end());
    std::sort(apartments.begin(), apartments.end());
    size_t cust_index{}, apart_index{};
    int cnt{};
    while (cust_index != customer.size() && apart_index != apartments.size())
    {
        int mincust{customer[cust_index] - k}, maxcust{customer[cust_index] + k};
        if (apartments[apart_index] < mincust)
        {
            apart_index++;
        }
        else if (apartments[apart_index] > maxcust)
        {
            cust_index++;
        }
        else
        {
            cnt++;
            apart_index++;
            cust_index++;
        }
    }
    std::cout << cnt << endl;
}
