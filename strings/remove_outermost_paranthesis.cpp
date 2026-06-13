/*
tc=O(n);
count the brackets and add to result if count>0
*/
#incude <bits/stdc++.h>
using namespace std;
string removeOuterParentheses(string s){
    string result="";
    int level=0;
    for(char ch:s){
        if(ch=='('){
            if(level>0) result+=ch;
            level++;
        }
        else if(ch==")"){
            level--;
            if(level>0) result+=ch;
        }
    } return result;
}
