/**
create two pointers fast and slow
move fast two steps and slow one step till fast||fast next react null ptr
return slow
 */
#include <bits/stdc++.h>
using namespace std;
    ListNode* middleNode(ListNode* head) {
         ListNode *slow = head; 
    
    ListNode *fast = head; 
    while (fast != NULL && fast->next != NULL) {
        slow = slow->next; 
        fast = fast->next->next; 
    }
    return slow; 
    }