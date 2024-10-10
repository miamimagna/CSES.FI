#include <iostream>
#include <vector>
#include <cstdint>
#define int long long
using namespace std;
void solve(){
    int n;
    cin >> n;
    int q = 5, ans = 0;
    while(q <= n){
        ans += n / q;
        q *= 5;
    }
    cout<< ans << endl;
}
signed main()
{
    // int n; cin>>n;
    // while(n --)
        solve();
}
