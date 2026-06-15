/*
count the bracekts increase if open and decrease if close bracket appears
tc=O(n)
*/
#incude <bits/stdc++.h>
using namespace std;
int maxDepth(string s){
    int p=0,ans=0;
    for(char x:s){
        if(x=='(') p++;
        else if(x==')') p--;
        ans=max(ans,p);
    } return ans;
}