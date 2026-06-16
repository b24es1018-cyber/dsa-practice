/*
one way is to increase counter then /2 and decrease till 0 and delete that node
another is fast slow approach
don't delete head on leetcode just skip it
*/
#include <bits/stdc++.h>
using namespace std;
ListNode* deleteMiddle(ListNode* head){
    if(head==nullptr || head->next==nullptr){
        delete head;
        return nullptr;
    }
    ListNode* slow=head;
    ListNode* fast=head->next->next;
    while(fast!=nullptr && fast->next!=nullptr){
        fast=fast->next->next;
        slow=slow->next;
    }
    ListNode* mid=slow->next;
    slow->next=slow->next->next;
    delete mid;
    return head;
}