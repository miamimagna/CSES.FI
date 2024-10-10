#include <iostream>
#include <utility>
using namespace std;
#define int long long
void tower(int n, int from, int th, int to)
{
    if (n == 0)
        return;
    tower(n - 1, from, to, th);
    cout << from << " " << to << "\n";
    tower(n - 1, th, from, to);
}
void solve()
{
    int n;
    cin >> n;
    cout << (1 << n) - 1 << "\n";
    tower(n, 1, 2, 3);
    return;
}
int32_t main()
{
    solve();
    cout << "\n";
    return 0;
}
