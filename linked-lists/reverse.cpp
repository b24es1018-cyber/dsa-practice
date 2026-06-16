/*
one method
push all elements in a stack(lifo) then mark temp=head
temp->val=st.top() temp=temp->next do while(temp!=NULL) return head  
another is to create front and previous and return prvious 
*/
#include <bits/stdc++.h>
using namespace std;
    ListNode* reverseList(ListNode* head) {
        ListNode* prev = NULL;
        ListNode* temp = head;
        while (temp != NULL) {
            ListNode* front = temp->next;

            temp->next = prev;
            prev = temp;
            temp = front;
        }
        return prev;
    }
    
