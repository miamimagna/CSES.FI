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
void solve()
{
    int n, m;
    cin >> n >> m;
    v<int> a(n);
    for(auto &x: a) 
        cin >> x;
    v<int> b(n + 2);
    for(int i = 0; i < n; i++)
        b[a[i]] = i + 1;
    b[0] = n + 1;
    int res = 0;
    for(int i = 1; i <= n; i++)
        if(b[i] < b[i - 1]) 
            res++;
    while(m--){
        int x, y;
        cin >> x >> y;
        int xi = a[x - 1], yi = a[y - 1];
        swap(a[x - 1], a[y - 1]);
        if(xi > yi) swap(xi, yi);
        // xi will contain smaller one!
        // old state
        int cnt = 0;
        if(b[xi] < b[xi - 1]) cnt++;
        if(yi - xi != 1 && b[yi] < b[yi - 1]) cnt++;
        if(b[xi] > b[xi + 1]) cnt++;
        if(b[yi] > b[yi + 1]) cnt++;
        
        swap(b[xi], b[yi]);
        if (b[xi] < b[xi - 1])
            cnt--;
        if (yi - xi != 1 && b[yi] < b[yi - 1])
            cnt--;
        if (b[xi] > b[xi + 1])
            cnt--;
        if (b[yi] > b[yi + 1])
            cnt--;
        res -= cnt;
        cout<<res<<endl;
    }
}
signed main()
{
    // int n; cin>>n;
    // while(n --)
    solve();
}
