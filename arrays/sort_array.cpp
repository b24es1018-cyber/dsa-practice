/*
first i think of choosing the peak element and check its right and left part but its not best 
right is to check if only one time a number can proceed its next index in rotated.

time complx=O(n)
space complx=O(1)
*/


#include <bits/stdc++.h>
using namespace std;
  bool check(vector<int>& nums) {
    int n = nums.size();
    int count = 0;

    for (int i = 0; i < n; i++) {
        if (nums[i] > nums[(i + 1) % n]) {
            count++;
        }
    }

    return count <= 1;
}
