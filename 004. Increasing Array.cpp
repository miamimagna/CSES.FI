#include<iostream>
#include<vector>
#include<cmath>
using namespace std;
#define int long long
signed main(){
    int n; cin>>n;
    vector<int> a(n);
    for(auto &x: a) cin>>x;
    int ans = 0;
    for(int i = 0; i < n - 1; i++)
        if(a[i] > a[i + 1]){
            int dif = a[i] - a[i + 1];
            ans += dif;
            a[i + 1] = a[i];
        }
    cout<<ans<<endl;
    
}
