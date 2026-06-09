/*
solve using low mid high tracking optimalyy 
but also solve using counting the digits and running iteration 
tc=O(n)
sc=O(1)
*/
#include <bits/stdc++.h>
using namespace std;
void sortColors(vector<int>& nums){
    int low=0,mid=0,high=nums.size()-1;
    while(mid<=high){
        if(nums[mid]==0){
            swap(nums[mid],nums[low]);
            low++;
            mid++;
        }
        else if(nums[mid]==1){
            mid++;
        }
        else {
            swap(nums[mid],nums[high]);
            high--;
        }
    }
}