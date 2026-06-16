/*
one way is to create a map and mark all addresses and return if it repeats
optimal is to create slow and fast pointers and run
when they meet reset slow to head and move each with only one position till they meet next 
meeting point is starting point of loop
*/
#include <bits/stdc++.h>
using namespace std;
ListNode *detectCycle(ListNode *head){
    ListNode* slow=head;
    ListNode* fast=head;
    while(fast!=nullptr && fast->next!=nullptr){
        slow=slow->next;
        fast=fast->next->next;
        if(slow==fast){
            slow=head;
            while(slow!=fast){
                slow=slow->next;
                fast=fast->next;
            } return slow;
        }
    } return NULL;
}