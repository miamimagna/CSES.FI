#include <iostream>
#include <vector>
#include <cstdio>
using namespace std;
class Fenwick
{
    vector<int> a;
    int n;

public:
    Fenwick(int nn) : a(nn), n(nn) {}
    Fenwick(vector<int> &arr) : Fenwick((int)arr.size())
    {
        for (int i = 0; i < n; i++)
        {
            a[i] ^= arr[i];
            int j = i | (i + 1);
            if (j < n)
                a[j] ^= a[i];
        }
    }
    int Xor(int i)
    {
        int res = 0;
        for (; i >= 0; i = (i & (i + 1)) - 1)
            res ^= a[i];
        return res;
    }
    int Xor(int l, int r)
    {
        return Xor(r) ^ Xor(l - 1);
    }
};
int main()
{
    int n, q;
    cin >> n >> q;
    vector<int> a(n);
    for (auto &x : a)
        cin >> x;
    Fenwick f(a);
    while (q--)
    {
        int l, r;
        cin >> l >> r;
        l--, r--;
        cout << f.Xor(l, r) << endl;
    }
}
