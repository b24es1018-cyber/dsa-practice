/*
first sort then check wether the the el-1 is present or not
optimal is to make a unordered set and check the current value-1 present or not
*/
#include <bits/stdc++.h>
using namespace std;
int longestConsecutive(vector<int>& nums){
    int n=nums.size();
    unordered_set<int>st;
    if(n==0)return 0;
    int longest=1;
    for(int i=0;i<n;i++){
        st.insert(nums[i]);
    }
    for(auto it:st){
        if(st.find(it-1)==st.end){
            int count=1;
            int x=it;
            while(st.find(x+1)!=st.end()){
                count++;
                x=x+1;
            }
            longest=max(longest,count);
        }
    } return longest;
}