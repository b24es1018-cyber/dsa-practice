/*
reverse only words create vector string
else start from end choose staring and ending
point for each word and add one by one adding spaces
*/
#incude <bits/stdc++.h>
using namespace std;
string reverseWords(string s){
    int i=s.size()-1;
    string result="";
    while(i>=0){
        while(i>=0 && s[i]==' '){
            i--;
        }
        if(i<0) break;
        int end=i;
        while(i>=0 && s[i]!=' '){
            i--;
        }
        string word=s.substr(i+1,end-1);
        if(!result.empty()){
            result+=" ";
        }
        result+=word;
    } return result;
}