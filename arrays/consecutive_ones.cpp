#include <bits/stdc++.h>
using namespace std;
int findMaxConsecutiveOnes(vector<int>& nums){
    int count=0;
    int num=0;
    for(int i=0;i<nums.size();i++){
        if(nums[i]==1){
            count++;
        }
        else count=0;
        num=max(count,num);
    } return num;
}