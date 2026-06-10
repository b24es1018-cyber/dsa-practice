/*
one method is to make separate row and coloumn to keep track of zeroes 
optimal is to make the very first row and column tracker and then mark accordingly
*/
#include <bits/stdc++.h>
using namespace std;
void setZeroes(vector<vector<int>>& matrix){
    int m=matrix.size();
    int n=matrix[0].size();
    bool firstrowzero=false;
    bool firstcolumnzero=false;
    for(int j=0;j<n;j++){
        if(matrix[0][j]==0){
            firstrowzero= true;
            break;
        }
    }
    for(int i=0;i<m;i++){
        if(matrix[i][0]==0){
            firstcolumnzero= true;
            break;
        }
    }
    for(int i=1;i<m;i++){
        for(int j=1;j<n;j++){
            if(matrix[i][j]==0){
                matrix[i][0]=0;
                matrix[0][j]=0; 
            }
        }
    }
    for(int i=1;i<m;i++){
        for(int j=1;j<n;j++){
            if(matrix[i][0]==0 || matrix[0][j]==0){
                matrix[i][j]=0;
            }
        }
    }
    if(firstrowzero){
        for(int j=0;j<n;j++){
            matrix[0][j]=0;
        }
    }
    if(firstcolumnzero){
        for(int i=0;i<m;i++){
            matrix[i][0]=0;
        }
    }
}   