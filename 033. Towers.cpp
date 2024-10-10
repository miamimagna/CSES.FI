#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
// #define int long long
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
void solve()
{
    int n; cin>>n;
    v<int> a;
    while(n--){
        int x; cin>>x;
        auto itr = ub(each(a), x);
        if(itr == a.end()) a.push_back(x);
        else *itr = x;
    }
    cout<<a.size()<<endl;
}
signed main()
{
    // int n; cin>>n;
    // while(n --)
    solve();
}
