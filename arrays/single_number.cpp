/*
xor is optimal but can also use hash method
*/
#include <bits/stdc++.h>
using namespace std;
int singleNumber(vector<int>& nums){
    int ans=0;
    for(int num:nums){
        ans^=num
    }
    return ans;
}
