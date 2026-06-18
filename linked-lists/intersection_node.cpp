/*
create a hashmap and track the values of list1 now search values of list 2 in hashmap
optimal is to make two pointers d1 and d2 and run both if they meets return 
if one reaches null point it to head of other so that length not effects the algo
*/
ListNode *getIntersectionNode(ListNode *headA, ListNode *headB){
    ListNode* d1=headA;
    ListNode* d2=headB;
    while(d1!=d2){
        d1=d1==NULL ? headB:d1->next;
        d2=d2==NULL ? headA:d2->next;
    }
    return d1;
}