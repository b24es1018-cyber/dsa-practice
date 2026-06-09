/*
two pointer approach is best for this first locate the first zero then proceed
tc=O(n)
sc=O(1)
*/

#include <bits/stdc++.h>
using namespace std;
void moveZeroes(vector<int>& nums) {
       
        int j = -1;
        for (int i = 0; i < nums.size(); i++) {
            if (nums[i] == 0) {
                j = i;
                break;
            }
        }
        if (j == -1) return;

        for (int i = j + 1; i < nums.size(); i++) {
            if (nums[i] != 0) {
                swap(nums[i], nums[j]);
                j++;
            }
        }
    }