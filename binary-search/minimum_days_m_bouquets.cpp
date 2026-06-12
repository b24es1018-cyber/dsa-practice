/*
**time complexity**
*/
#include <bits/stdc++.h>
using namespace std;
bool possible(vector<int>arr,int day,int m,int k){
    int count=0,bouq=0;
    for(auto it:arr){
        if(it<=day){
            count++;
            if(count==k){
                bouq++;
                count=0;
            }
        }
        else count=0;
    } return bouq>=m;
}
int minDays(vector<int>& bloomDay, int m, int k){
    int n=bloomDay.size();
    if(m*k>n) return -1;
    int ans=-1;
    int low=*min_element(bloomDay.begin(),bloomDay.end());
    int high=*max_element(bloomDay.begin(),bloomDay.end());
    while(low<=high){
        int mid=(low+high)/2;
        if(possible(bloomDay,mid,m,k)){
            ans=mid;
            high=mid-1;
        }
        else low=mid+1;
    } return ans;
}