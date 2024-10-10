#include <bits/stdc++.h>
using namespace std;
int main()
{
    int n;
    cin >> n;
    vector<int> a(n);
    long long sum{};
    for (auto &x : a)
        cin >> x, sum += x;
    int mx = *max_element(a.begin(), a.end());
    sum -= mx;
    if (sum < mx)
        cout << 2 * mx << endl;
    else
        cout << sum + mx << endl;
}
