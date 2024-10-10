#include <iostream>
#include <vector>
#include <cstdint>
#define int long long
using namespace std;
int mod = 1e9 + 7;
int pow(int n, int x){
    if(x == 0) return 1;
    int res = pow(n, x >> 1);
    if(x & 1) return (((n * res) % mod) * res) % mod;
    else return (res * res) % mod;
}
void solve(){
    int n;
    cin >> n;
    cout << pow(2, n) << endl;
}
signed main()
{
        solve();
}
