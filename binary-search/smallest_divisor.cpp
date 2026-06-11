/*
first take ceil and then do binar search but beaware of timeout
return low as its equal to same as mid
*/
#include <bits/stdc++.h>
using namespace std;
int ansh(vector<int> & nums, int divisor){
    int ans=0;
    for(int it:nums){
        ans+=ceil((double)it/divisor);
    } return ans;
}
int smallestDivisor(vector<int>& nums, int threshold){
    int m=*max_element(nums.begin(),nums.end());
    int low=1,high=m;
    int ans=m;
    while(low<=high){
        int mid=(low+high)/2;
        if(ansh(nums,mid)<=threshold){
            high=mid-1;
        }
        else{
            low=mid+1;
        }
    } return low;
}