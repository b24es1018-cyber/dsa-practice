/*
first check by rotating one by one like substrs(i)+substrs(0,i);
or
double the string and now find the goal string inside it if not found return false
*/
#incude <bits/stdc++.h>
using namespace std;
bool rotateString(string s, string goal){
    if(s.length()!=goal.length()) return false;
    string doubleds=s+s;
    return doubleds.find(goal)!=string::npos;
}