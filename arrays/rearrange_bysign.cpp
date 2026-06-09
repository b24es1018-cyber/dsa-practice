/*
first thought of making 2 diff araays of pos & neg and megrge to respective index
but optimal is to make another separate array and push one by one also increase index by 2 respectively
*/
#include <bits/stdc++.h>
using namespace std;
vector<int> rearrangeArray(vector<int>& nums){
    vector<int>ans(nums.size(),0);
    int posind=0,negind=1;
    for(int i=0;i<nums.size();i++){
        if(nums[i]<0){
            ans[negind]=nums[i];
            negind+=2;
        }
        else{
            ans[posind]=nums[i];
            posind+=2;
        }
    } return ans;
}