/*
review the whole problem
*/
#include <bits/stdc++.h>
using namespace std;
int countPartitions(vector<int>& nums, int maxSum) {
    int partitions = 1;
    int subSum = 0;

    for (int x : nums) {
        if (subSum + x <= maxSum) {
                subSum += x;
            } else {
                partitions++;
                subSum = x;
            }
        }

        return partitions;
    }

    int splitArray(vector<int>& nums, int k) {
        int low = *max_element(nums.begin(), nums.end());
        int high = accumulate(nums.begin(), nums.end(), 0);

        int ans = high;

        while (low <= high) {
            int mid = low + (high - low) / 2;

            int partitions = countPartitions(nums, mid);

            if (partitions > k) {
                low = mid + 1;
            } else {
                ans = mid;
                high = mid - 1;
            }
        }

        return ans;
    }