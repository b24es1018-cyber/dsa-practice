/*
For Right Rotation by k steps:
Reverse the entire array
Reverse the first k elements
Reverse the remaining n - k elements
  
For Left Rotation by k steps:
Reverse the first k elements
Reverse the remaining n - k elements
Reverse the entire array
*/
#include <bits/stdc++.h>
using namespace std;
void reverseArray(vector<int>& nums, int start, int end) {
        while (start < end) {
            swap(nums[start], nums[end]);
            start++;
            end--;
        }
    }
void rotate(vector<int>& nums, int k){
  int n=nums.size();
  if(n==0||k==0) return;
  k=k%n;
  reverseArray(nums,0,nums.size()-1);
   reverseArray(nums,0,k-1);
   reverseArray(nums,k,nums.size()-1);
 

} 