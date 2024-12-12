#include <iostream>
#include <vector>
using namespace std;
vector<vector<int>> adj;
vector<int> cnts;
int dfs(int i){
    int cnt = 0;
    for(int child: adj[i])
        cnt += dfs(child) + 1;
    return cnts[i - 1] = cnt;
}
int main(){
    int n; cin >> n;
    adj.resize(n + 1);
    cnts.resize(n);
    for(int i = 2; i <= n; i++){
        int x; cin >> x;
        adj[x].push_back(i);
    }
    dfs(1);
    for(auto x: cnts)
        cout << x << ' '; cout << endl;
}
