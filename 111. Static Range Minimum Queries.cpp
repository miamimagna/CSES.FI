#include <iostream>
#include <vector>
#include <functional>
#include <algorithm>
using namespace std;
long long lg2(long long x)
{
    return x ? __builtin_clzll(1) - __builtin_clzll(x) : -1;
}
template <typename T, class U = function<T(const T &, const T &)>>
class Sparse_table
{
    size_t n, k;
    vector<vector<T>> st;
    vector<long long> lg;
    U op;
 
public:
    Sparse_table() = default;
    Sparse_table(const vector<T> &arr, const U &OP)
    {
        n = arr.size(), k = lg2(n) + 1, op = OP;
        st.resize(k + 1, vector<T>(n));
        lg.resize(n + 1);
        lg[1] = 0;
        for (int i = 2; i <= n; i++)
            lg[i] = lg[i / 2] + 1;
        st[0] = arr;
        for (int j = 1; j <= k; j++)
            for (int i = 0; i + (1 << j) <= n; i++)
                st[j][i] = op(st[j - 1][i], st[j - 1][i + (1 << (j - 1))]);
    }
    T query(int l, int r)
    {
        if (l > r)
            return T();
        long long j = lg[r - l + 1];
        return op(st[j][l], st[j][r - (1 << j) + 1]);
    }
};
#include <cstdio>
int main()
{
    int n, q;
    cin >> n >> q;
    vector<int> a(n);
    for (auto &x : a)
        cin >> x;
    Sparse_table<int> st(a, [](const int &a, const int &b)
                         { return min(a, b); });
    while (q--)
    {
        int l, r;
        cin >> l >> r;
        l--, r--;
        cout << st.query(l, r) << endl;
    }
}
