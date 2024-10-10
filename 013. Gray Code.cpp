#include<iostream>
#include<vector>
#include<string>
using namespace std;
int main()
{
int n; cin>>n;
vector<vector<string>> a(n);
string z{"0"}, o{"1"};
a[0]={z,o};
for(int i=1; i<n;i++)
{
for(auto s: a[i-1])
{
string temp= z+s;
a[i].push_back(temp);
}
for (int j=a[i-1].size()-1; j>=0; j--)
{
string temp= o+a[i-1][j];
a[i].push_back(temp);
}
}
for(auto x: a[n-1])
cout<<x<<endl;
}
