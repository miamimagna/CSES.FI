#include <iostream>
#include <algorithm>
#include <climits>
using namespace std;
#define int long long
#define endl '\n'
signed main()
{
    int n;
    int count{1};
    cin >> n;
    int arr[n];
    for (int i = 0; i < n; i++)
    {
        cin >> arr[i];
    }
    std::sort(arr, arr + n);
    for (int i = 1; i < n; i++)
        if (arr[i] != arr[i - 1])
            count++;
    cout << count << endl;
}
