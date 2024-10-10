#include <iostream>
#include <vector>
#include <cstdint>
#include <utility>
#define int long long
using namespace std;
void solve(){
    int a, b;
    cin >> a >> b;
    if (a < b) swap(a, b);
    int mx = a * 2;
    mx -= b;
    if(b < a / 2) mx = -1;
    if(mx < 0 || mx % 3) cout << "NO" << endl;
    else cout<<"YES"<<endl;
}
signed main()
{
    int n; cin>>n;
    while(n --)
        solve();
}
