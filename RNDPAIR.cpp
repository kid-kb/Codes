#include<bits/stdc++.h>
using namespace std;
main()
{
	int t;
	cin>>t;
	for(int i=0;i<t;i++)
	{
		int n;
		cin>>n;
		int arr[n];
		for(int j=0;j<n;j++)
			cin>>arr[j];
			
		int total = (n)*(n-1)/2;
		int max = INT_MIN;
		int count = 0;
		int sum = 0;
		
		for(int j=0;j<n-1;j++)
		{
			sum = 0;
			for(int k=j+1;k<n;k++)
			{
				sum = arr[j] + arr[k];
				
				if(sum > max)
				max = sum;
			}	
		}
		
		for(int j=0;j<n-1;j++)
		{
			sum = 0;
			for(int k=j+1;k<n;k++)
			{
				sum = arr[j] + arr[k];
			
				if(sum == max)
					count++;
			}		
		}
		cout<<((float)count)/total<<"\n";
	}
}
