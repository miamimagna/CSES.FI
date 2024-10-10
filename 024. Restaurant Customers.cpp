#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
int main()
{
    int n;
    cin >> n;
    vector<vector<int>> a;
    while (n--)
    {
        int j, k;
        cin >> j >> k;
        a.push_back({j, 1}), a.push_back({k, -1});
    }
    sort(a.begin(), a.end());
    int current{0}, cmax{};
    for (int i = 0; i < a.size(); i++)
    {
        current += a[i][1];
        if (current > cmax)
            cmax = current;
    }
    cout << cmax << endl;
}
