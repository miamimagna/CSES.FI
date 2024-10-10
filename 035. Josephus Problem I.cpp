#include<bits/stdc++.h>
using namespace std;
 
#define endl '\n'
 
signed main(){
    #ifdef LOCAL
    freopen("input.txt", "r" , stdin);
    freopen("output.txt", "w", stdout);
    #endif
    
    int n; scanf("%d",&n);
    int a = 1, b = 0;
    while(n > 0) {
    	for (int i = 2; i <= n; i+=2) {
    		printf("%d ",a*i + b);
    	}
    	if (n&1) printf("%d ",a + b), b += a;
    	else b -= a;
    	a <<= 1;
    	n >>= 1;
    }
