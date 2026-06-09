/*
first sort then move pointer left and right side also track original indices using hashmap
also solve by maping the values and and find using iterating the remaining value
*/
#include <bits/stdc++.h>
using namespace std;
vector<int> twoSum(vector<int>& nums, int target){
    int n=nums.size();
    vector<pair<int,int>>numswithindex;
    for(int i=0;i<n;i++){
        numswithindex.push_back({nums[i],i});
    }
    sort(numswithindex.begin(),numswithindex.end());
    int left=0,right=n-1;
    while(left<right){
        int sum=numswithindex[left].first+numswithindex[right].first;
        if(sum==target){
            return {numswithindex[left].second, numswithindex[right].second};
        }
        else if(sum<target) left++;
        else right--;
    } return{-1,-1};
}