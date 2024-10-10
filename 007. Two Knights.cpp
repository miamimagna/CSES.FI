#include <iostream>
#include <vector>
#include <cstdint>
#define int long long
using namespace std;
signed main()
{
    int t;
    cin >> t;
    for (int k = 1; k <= t; k++)
    {
        if (k == 1)
        {
            cout << 0 << endl;
        }
        else
        {
            // ideally each piece can have a piece at any other spot
            int sq = k * k, ans = sq * (sq - 1);
            if (k > 2)
            {
                int total = sq;
                // for corner knights
                ans -= 8, total -= 4;
                // when piece is right next to corner
                if (k == 3)
                    ans -= 8, total -= 4;
                else
                    ans -= 6 * 4, total -= 8;
                // rest of boundary pieces
                if (k > 3)
                {
                    ans -= 4 * 4 * (k - 4), total -= 4 * (k - 4);
                    // now 2nd level element
                    ans -= 4 * 4, total -= 4;
                    ans -= 4 * 6 * (k - 4), total -= 4 * (k - 4);
                    ans -= 8 * total;
                }
            }
            cout << ans / 2 << endl;
        }
    }
}
