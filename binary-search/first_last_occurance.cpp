/*
also traverse from first and last as array is sorted 
but optimal is to use bunary approach
*/
#include <bits/stdc++.h>
using namespace std;
vector<int> searchRange(vector<int>& nums, int target){
   vector<int> ans;
    int n=nums.size()-1;
   int low=0,high=n;
   int first=-1,last=-1;
   while(low<=high){
    int mid=(low+high)/2;
    if(nums[mid]==target){
        first=mid;
        high=mid-1;
    }
    else if (nums[mid]<target){
        low=mid+1;
    }
    else high=mid-1;
   } 
   low=0;
   high=n;
    while(low<=high){
    int mid=(low+high)/2;
    if(nums[mid]==target){
        last=mid;
        low=mid+1;
    }
    else if (nums[mid]<target){
        low=mid+1;
    }
    else high=mid-1;
   } ans.push_back(first);
   ans.push_back(last);
   return ans;
}