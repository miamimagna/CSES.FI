#include<iostream>
#include<vector>
#include<cmath>
using namespace std;
int main(){
    string s; 
    cin>>s;
    int ans = 1, cnt = 1;
    for(int i = 1; i < s.size(); i++){
        if(s[i] == s[i - 1]) cnt++;
        else cnt = 1;
        ans = max(ans, cnt);
    }
    cout<<ans<<endl;
}
