#include<bits/stdc++.h>
using namespace std;
int n;
long long s,s1,s2;
vector<int> a,b;
int main()
{
	cin>>n;
	s=1ll*(1+n)*n/2;
	if(s&1) cout<<"NO\n";
	else
	{
		cout<<"YES\n";
		s/=2;
		for(int i=n;i>=1;i--)
		{
			if(s1+i<=s)
			{
				a.push_back(i);
				s1+=i;
			}
			else
			{
				b.push_back(i);
				s2+=i;
			}
		}
		cout<<a.size()<<"\n";
		for(int i=0;i<a.size();i++) cout<<a[i]<<" ";
		cout<<"\n"<<b.size()<<"\n";
		for(int i=0;i<b.size();i++) cout<<b[i]<<" ";
		cout<<"\n";
	}
	return 0;
}
