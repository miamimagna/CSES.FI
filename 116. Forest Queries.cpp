#include <iostream>
#include <vector>
#include <cstdio>
using namespace std;
#define int long long
class FenwickTree2D
{
private:
    vector<vector<int>> a;
#define g(i) (i & (i + 1))
#define h(i) (i | (i + 1))
public:
    FenwickTree2D(int n, int m) : a(n, vector<int>(m)) {}
    FenwickTree2D(vector<vector<int>> &v) : FenwickTree2D(v.size(), v[0].size())
    {
        for (int i = 0; i < v.size(); i++)
            for (int j = 0; j < v[0].size(); j++)
                update(i, j, v[i][j]);
    }
    long long sum(int x, int y)
    {
        long long res = 0;
        for (int i = x; i != -1; i = g(i) - 1)
            for (int j = y; j != -1; j = g(j) - 1)
                res += a[i][j];
        return res;
    }
    long long sum(int x, int y, int a, int b)
    {
        x--, y--;
        return sum(a, b) - sum(a, y) - sum(x, b) + sum(x, y);
    }
    void update(int x, int y, int delta)
    {
        for (int i = x; i < a.size(); i = h(i))
            for (int j = y; j < a[0].size(); j = h(j))
                a[i][j] += delta;
    }
};
signed main()
{
    int n, q;
    cin >> n >> q;
    vector<vector<int>> a(n, vector<int>(n));
    for (auto &x : a)
        for (auto &y : x)
        {
            char ch;
            cin >> ch;
            y = ch == '*';
        }
    FenwickTree2D f2d(a);
    while (q--)
    {
        int y1, x1, y2, x2;
        cin >> y1 >> x1 >> y2 >> x2;
        cout << f2d.sum(y1 - 1, x1 - 1, y2 - 1, x2 - 1) << endl;
    }
}
