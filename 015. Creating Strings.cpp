#include <iostream>
#include <vector>
#include <string>
#include <unordered_set>
#include <algorithm>
#define int long long
using namespace std;
// preprocessing to make code easier 
template <typename T> 
using v = vector<T>; 
#define maxheap(T) priority_queue<T> 
#define minheap(T) priority_queue<T, v<T>, greater<T>> 
#define heap(T, comp) priority_queue<T, v<T>, comp> 
#define ff first 
#define ss second 
#define sz size() 
#define pb push_back 
#define eb emplace_back 
#define sortc(a, comp) sort(a.begin(), a.end(), comp) 
#define sortv(a) sort(a.begin(), a.end()) 
#define each(a) a.begin(), a.end() 
#define lb lower_bound 
#define ub upper_bound
void solve(){
    string s; cin>>s;
    int cnt = 1;
    sortv(s);
    string answer = s;
    while(next_permutation(each(s)))
        cnt++,
        answer += '\n' + s;
    cout << cnt << endl << answer << endl;
}
signed main()
{
    // int n; cin>>n;
    // while(n --)
    solve();
}
