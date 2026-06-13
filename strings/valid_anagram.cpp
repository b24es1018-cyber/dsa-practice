/*
one way is to sort first thhen compare
another is to compare the frequency of each position ans[26]
*/
#include <bits/stdc++.h>
using namespace std;
bool isAnagram(string s, string t){
    if(s.length()!=t.length()) return false;
    int n=t.length();
    int freq[26]={0};
    for(int i=0;i<n;i++){
       freq[s[i]-'a']++;
    }
    for(int i=0;i<n;i++){
       freq[t[i]-'a']--;
    }
    for(int i=0;i<26;i++){
        if(freq[i]!=0) return false;
    } return true;
}