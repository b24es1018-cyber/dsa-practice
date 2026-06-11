/*
also done using i=1 to max value in array 
optimal is binary search and using ceil value
also take care of runtime error
*/
#include <bits/stdc++.h>
using namespace std;
int totalhour(vector<int>& nums,int speed){
    int totalh=0;
    for(int it:nums){
        totalh+=ceil((double)it/speed);
    } return totalh;
}
int minEatingSpeed(vector<int>& piles, int h){
    int ans=*max_element(piles.begin(),piles.end());
    int low=1,high=*max_element(piles.begin(),piles.end());
    while(low<=high){
        int mid=(low+high)/2;
        int bph=totalhour(piles,mid);
        if(bph<=h){
            ans=mid;
            high=mid-1; 
        }
        else{
            low=mid+1;
        }
    } return ans;
}