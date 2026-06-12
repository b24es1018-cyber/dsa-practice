/*
if the value at index is lower than k increase 
k value by one then increase index and compare again
*/
#include <bits/stdc++.h>
using namespace std;
int findKthPositive(vector<int>& arr, int k){
    int n=arr.size();
    for(int i=0;i<n;i++){
        if(arr[i]<=k){
            k++;
        }
        else break;
    } return k;
}
