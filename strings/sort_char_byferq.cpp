/*
first store in map then convert in vector 
then sort 
*/
#incude <bits/stdc++.h>
using namespace std;
string frequencySort(string s){
    unordered_map<char,int>freq;
    for(char c:s){
        freq[char]++;
    }
    vector<pair<char,int>> vec(freq.begin(),freq.end());
    sort(vec.begin(),vec.end(),
    [](const pair<char,int>&a,const pair<char,int>&b){
        if(a.second != b.second) return a.second>b.second;
        return a.first<b.first;
    });
    string result="";
    for(const auto& it:vec){
        result.append(it.second,it.first);
    }
    return result;
}