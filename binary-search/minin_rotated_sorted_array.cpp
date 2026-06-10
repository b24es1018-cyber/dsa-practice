/*
first check wether mis is greater than high if yes then smallest lie on right side
else on left side including mid
here is low<high because if not it become infinite loop
*/
#include <bits/stdc++.h>
using namespace std;
int findMin(vector<int>& nums){
    int low=0,high=nums.size()-1;
    while(low<high){
        int mid=(low+high)/2;
        if(nums[mid]>nums[high]){
            low=mid+1;
        }
        else high=mid;
    } return nums[low];
}