#include<bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
using namespace __gnu_pbds;
using namespace std;
 // had to go all out used policy based data structure, explicit and fastest method for printing and processing input
typedef tree<int,null_type,less<int>,rb_tree_tag, tree_order_statistics_node_update> indexed_set;
#define endl '\n'
template <typename T>
void fastscan(T &destination) // faster input
{
    destination = 0;
    int n = getchar_unlocked();
    bool neg{};
    if (n == '-') // negative sign entered
    {
        neg = 1;
        n = getchar_unlocked();
    }
    for (; n >= '0' && n <= '9'; n = getchar_unlocked())
    {
        destination = destination * 10 + n - '0'; // it's merging
    }
    if (neg)
        destination = -1 * destination;
}
template <typename T>
void print(T value) // faster output
{
    if (value < 0) // put negative sign
    {
        putchar_unlocked('-');
        value = -value;
    }
    char digits[10];
    int i{10};
    do
    {
        digits[--i] = value % 10 + '0';
        value /= 10;
    } while (value);
    do
    {
        putchar_unlocked(digits[i]);
    } while (++i < 10);
}
signed main(){
    ios_base::sync_with_stdio(false);cin.tie(0);cout.tie(0);
    
    indexed_set s;
    int n,k; fastscan(n);
    fastscan(k);
    for (int i = 1; i <= n; i++)
        s.insert(i);
 
    int ind = k%n;
    while(n--) {
        auto y = s.find_by_order(ind);
        print(*y); putchar_unlocked(' ');
        s.erase(y);
        if (n) ind = (ind%n + k)%n;
    }   
}
