#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
int main()
{
    int n;
    cin >> n;
    vector<vector<int>> a;
    for (int i = 0; i < n; i++)
    {
        int j, k;
        cin >> j >> k;
        a.push_back({k, j});
    }
    sort(a.begin(), a.end());
    int i{}, j{1}, count{1};
    if (n == 1)
    {
        cout << 1 << endl;
        return 0;
    }
    while (j < n && i < n)
        if (a[i][0] > a[j][1])
            j++;
        else
            i = j, count++, j++;
    cout << count << endl;
}
