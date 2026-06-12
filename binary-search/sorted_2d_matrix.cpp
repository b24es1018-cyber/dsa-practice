/*
one approach is to binary seaech in a particular row wise
optimal is to falten the 2-D matrix 
by row=mid/m and column=mid%m then do BS
*/
#include <bits/stdc++.h>
using namespace std;
bool searchMatrix(vector<vector<int>>& matrix, int target){
   int n=matrix.size();
   int m=matrix[0].size();
   int low=0,high=n*m-1;
   while(low<=high){
    int mid=(low+high)/2;
    int row=mid/m;
    int column=mid%m;
    if(matrix[row][column]==target) return true;
    else if (matrix[row][column] < target){
        low=mid+1;
    }
    else high=mid-1;
   }  return false;
}