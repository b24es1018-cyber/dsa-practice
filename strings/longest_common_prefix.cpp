/*
sort the vector string then take min length from ffirst and last word
then compare each
*/
#incude <bits/stdc++.h>
using namespace std;
string longestCommonPrefix(vector<string>& strs){
    if(strs.empty()) return "";
    sort(strs.begin(),strs.end());
    int n=strs.size();
    string first=strs[0];
    string last=strs[n-1];
    string ans="";
    int minl=min(first.size(),last.size());
    for(int i=0;i<minl;i++){
        if(first[i]==last[i]) ans+=first[i];
        else break;
    } return ans;
}