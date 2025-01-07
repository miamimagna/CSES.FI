#include <iostream>
#include <cstdio>
#include <algorithm>
#include <vector>
#include <unordered_map>
#include <string>
#include <iomanip>
#include <set>
#include <unordered_set>
#include <queue>
#include <bitset>
using namespace std;
// preprocessing to make code easier
#define int long long
template <typename T>
using v = vector<T>;
signed main()
{
#ifdef LOCAL
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
    ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);
    int n, max_weight;
    cin >> n >> max_weight;
    v<int> weights(n);
    for (auto &x : weights)
        cin >> x;
    v<int> rides(1 << n, 1e9), last(1 << n, max_weight);
    rides[0] = 0;
    v<bool> vis(1 << n);
    queue<int> q;
    q.push(0);
    vis[0] = 1;
    while (q.size())
    {
        int m = q.size();
        while (m--)
        {
            int subset = q.front();
            q.pop();
            for (int i = 0; i < n; i++)
                if (!(subset & (1 << i)))
                {
                  // added set is what we will get after adding element
                    int added_set = subset + (1 << i);
                  // if minimum weight of last ride can accomodate passenger n, add it and don't increase ride
                    if (last[subset] + weights[i] <= max_weight)
                    {
                        // if rides are greater, make them less
                        if (rides[added_set] > rides[subset])
                            last[added_set] = last[subset] + weights[i],
                            rides[added_set] = rides[subset];
                        // if equal get better last weight
                        else if (rides[added_set] == rides[subset])
                            last[added_set] = min(last[subset] + weights[i], last[added_set]);
                    }
                    // otherwise increase ride now minimum last ride could be either last[subset] or the new weight we are putting
                    else
                    {
                      // same logic as above
                        if (rides[added_set] > rides[subset] + 1)
                            rides[added_set] = rides[subset] + 1,
                            last[added_set] = min(last[subset], weights[i]);
                        else if (rides[added_set] == rides[subset] + 1)
                            last[added_set] = min(last[added_set], min(last[subset], weights[i]));
                    }
                    if (!vis[added_set])
                        q.push(added_set), vis[added_set] = 1;
                }
        }
    }
    cout << rides.back() << endl;
}
