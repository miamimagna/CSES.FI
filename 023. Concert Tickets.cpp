#include <iostream>
#include <vector>
#include <algorithm>
#define endl '\n'
 
int replacement[200000], tickets[200000]; // -2 = unused, if used, replacement will store
int solve(int index)                      // index to the previously used value as replacement
{
    if (index < 0)
        return -1;
    if (replacement[index] == -2) // direct match
    {
        replacement[index] = index - 1;
        return index;
    }
    // otherwise search backwards till found
    replacement[index] = solve(replacement[index]);
    return replacement[index];
}
int main()
{
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(0);
    int n, m;
    std::cin >> n >> m;
    for (int i = 0; i < n; i++)
    {
        std::cin >> tickets[i];
        replacement[i] = -2;
    }
    std::sort(tickets, tickets + n);
    while (m--)
    {
        int t;
        std::cin >> t;
        int index = solve(std::upper_bound(tickets, tickets + n, t) - tickets - 1);
        if (index < 0)
            std::cout << -1 << endl;
        else
            std::cout << tickets[index] << endl;
    }
}
