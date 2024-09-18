#include<iostream>
#include<bits/stdc++.h>
using namespace std;

void QuickSort(int i, int j, int nums[], int n)
{
	if(i >= j) return;
	int pivot = i;
	int l = i, r = j;
	while(l<=r)
	{
		if(nums[l] <= nums[pivot])
		{
			l++;
			continue;
		}
		if(nums[r] >= nums[pivot])
		{
			r--;
			continue;
		}
		swap(nums[l],nums[r]);
	}
	swap(nums[pivot],nums[l-1]);
	QuickSort(i,l-2,nums,n);
	QuickSort(l,j,nums,n);
}

int main()
{
	int nums[] = {1,7,2,9,4,0,10,3,4,15,5};
	int n = sizeof(nums)/sizeof(nums[0]);
	cout<<"n = "<<n<<endl;
	QuickSort(0,n-1,nums,n);
	for(int i=0;i<n;i++)
		cout<<*(nums+i)<<" ";
	cout<<endl;
}