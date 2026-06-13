/*
find the last odd digit and exclude all zeroes from starting
*/
#incude <bits/stdc++.h>
using namespace std;
string largestOddNumber(string num){
    int n=num.size()-1;
    int ind=-1;
    for(int i=n;i>=0;i--){
        if((num[i]-'0')%2==1){
            ind=i;
            break;
        }
    }
    int i=0;
    while(i<n && num[i]=='0') i++;
    return num.substr(i,ind-i+1);
}