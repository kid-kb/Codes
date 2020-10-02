#include<bits/stdc++.h>
using namespace std;
void swap(char *a,char *b)
{
	char temp = *a;
	*a = *b;
	*b = temp;
}
main()
{
	int t;
	cin>>t;
	while(t--)
	{
		int n;
		cin>>n;
		int l[n],g[n];
		for(int i=0;i<n;i++)
			cin>>l[i];
		for(int i=0;i<n;i++)
			cin>>g[i];
			
		int flag1 = 0,flag2 = 0;
		int count = 0;	
		for(int i=0;i<n;i++)
		{
			if(l[i] <= g[i])
				count++;
		}
		if(count == n)
			flag1++;
			
		count = 0;	
		for(int i=0;i<n;i++)
		{
			if(l[i] <= g[n-i-1])
				count++;
		}
		if(count == n)
			flag2++;
		
		if(flag1 == 1 && flag2 == 0)
			cout<<"front"<<"\n";
		else if(flag1 == 0 && flag2 == 1)
			cout<<"back"<<"\n";
		else if(flag1 == 1 && flag2 == 1)
			cout<<"both"<<"\n";
		else
			cout<<"none"<<"\n";
	}
}
