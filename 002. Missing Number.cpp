#include<iostream>
#include<vector>
#include<cmath>
using namespace std;
int main(){
    int n; cin>>n;
    vector<int> a(n - 1);
    for(auto &x: a) cin>>x;
    for(auto x: a){
        x = abs(x);
        if(x != n) a[x - 1] *= -1;
    }
    int ans = n;
    for(int i = 0; i < n; i++)
        if(a[i] > 0) {
            ans = i + 1;
            break;
        }
    cout<< ans << endl;
}
