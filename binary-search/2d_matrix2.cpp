/*
first apply BS rowwise 
but optimal is to choose top right corner and
increase row if current<target else decrease col 
*/
#include <bits/stdc++.h>
using namespace std;
bool searchMatrix(vector<vector<int>>& matrix, int target){
   int row=0;
   int col=matrix[0].size()-1;
   while(row<matrix.size() && col>=0){
    if(matrix[row][col]==target) return true;
    else if(matrix[row][col]<target){
        row++;
    }
    else col--;
   } return false;
}