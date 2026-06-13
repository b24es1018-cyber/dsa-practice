/*
first store string characters into  arr and increase by value by one
then match each value 
*/
#incude <bits/stdc++.h>
using namespace std;
bool isIsomorphic(string s, string t){
    int m1[256]={0},m2[256]={0};
    int n=s.size();
    for(int i=0;i<n;i++){
        if(m1[s[i]]!=m2[t[i]]) return false;
        m1[s[i]]=i+1;
        m2[t[i]]=i+1;
    } return true;
}