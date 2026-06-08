/*
firstly i think of sets but for optimal i use two pointer 
tc=O(n)
sc=O(1)
*/
#include <bits/stdc++.h>
using namespace std;
int remove_duplicates(vector<int>& nums){
  int n=nums.size();
  int i=0;
   for (int j=1;j<n;j++){
    if(nums[i]!=nums[j]){
        i++;
        nums[i]=nums[j];
    }
  } return i+1;
}
