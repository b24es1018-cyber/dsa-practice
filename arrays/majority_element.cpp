/*
also done using hash map
but done by tracking the element and increase count if same element otherwise reduce the count if count is zero select next element
*/
#include <bits/stdc++.h>
using namespace std;
int majorityElement(vector<int>& nums){
    int count=0;
    int el;
    for(int i=0;i<nums.size();i++){
        if(count==0){
            count=1;
            el=nums[i];
        }
        else if(nums[i]==el){
            count++;
        }
        else count--;
    }
    int count1=0;
    for(int i=0;i<nums.size();i++){
        if(nums[i]==el) count1++;
    }
    if(count1>(n/2)){
        return el;
    } return -1;
}