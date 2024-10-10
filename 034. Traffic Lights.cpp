#include <cstdio>
#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <utility>
#include <set>
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
    int x, n;
    cin >> x >> n;
    v<int> a(n);
    for(auto &x: a) 
        cin >> x;
    set<pair<int, int>> s;
    s.insert({1, x});
    multiset<int> gap;
    gap.insert(x);
    for(auto x: a){
        pair<int, int> pi = {x, 1e9};
        auto itr = s.ub(pi);
        itr--;
        auto temp = *itr;
        s.erase(itr);
        gap.erase(gap.find(temp.second - temp.first + 1));
        gap.insert(x - temp.first + 1);
        gap.insert(temp.second - x);
        s.insert({temp.first, x});
        s.insert({x + 1, temp.second});
        cout << *gap.rbegin()<<' ';
    }
    cout<<endl;
}
signed main()
{
    solve();
}
