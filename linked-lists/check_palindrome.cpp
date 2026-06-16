/*
put all values in stack,assign temp=head again then match st.top and temp->data
optimal is to make slow&fast pointers and reach mid
now reverse the second have and compare both 
before returning reverse again for original
*/
#include <bits/stdc++.h>
using namespace std;
ListNode* revll(ListNode* head){
    if(head==NULL || head->next==NULL){
        return head;
    }
    ListNode* newhead=revll(head->next);
    ListNode* front=head->next;
    front->next=head;
    head->next=NULL;
    return newhead;
}
bool isPalindrome(ListNode* head){
    if(head==NULL||head->next==NULL){
        return true;
    }
    ListNode* slow=head;
    ListNode* fast=head;
    while (fast->next != NULL && fast->next->next != NULL){
        slow=slow->next;
        fast=fast->next->next;
    }
    ListNode* newhead=revll(slow->next);
    ListNode* first=head;
    ListNode* second=newhead;
    while(second!=NULL){
        if(first->val!=second->val){
            revll(newhead);
            return false;
        }
        first=first->next;
        second=second->next;
    }
    revll(newhead);
    return true;
}