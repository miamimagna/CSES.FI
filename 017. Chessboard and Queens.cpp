#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
using namespace std;
const size_t maxn = 8;
int cnt{};
bool row[maxn], ld[2 * maxn - 1], rd[2 * maxn - 1];
string s[maxn];
bool check(int i, int j)
{
    if (row[j] == 0 && ld[i + j] == 0 && rd[i - j + maxn - 1] == 0)
        return true;
    return false;
}
void generate(int n)
{
    if (n == maxn)
    {
        cnt++;
        return;
    }
    for (int i = 0; i < maxn; i++)
    {
        if (check(n, i) && s[n][i] == '.')
        {
            row[i] = true, ld[i + n] = true, rd[n - i + maxn - 1] = true;
            generate(n + 1);
            row[i] = 0, ld[i + n] = 0, rd[n - i + maxn - 1] = 0;
        }
    }
}
int main()
{
    for (int i = 0; i < maxn; i++)
        cin >> s[i];
    generate(0);
    cout << cnt << endl;
}
