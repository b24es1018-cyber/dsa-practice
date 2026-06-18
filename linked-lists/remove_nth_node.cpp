/*
count the elements then res=count-N traverse till res beacome 0 then delete that node
optimal is to take fast pointer till N distance from beginning then move both fast and slow one step till fast reach end
*/
ListNode* removeNthFromEnd(ListNode* head, int n){
    ListNode* dummy=new ListNode(0,head);
    ListNode* fast=dummy;
    ListNode* slow=dummy;
    for(int i=0;i<=n;i++){
        fast=fast->next;
    }
    while(fast!=NULL) {
        fast=fast->next;
        slow=slow->next;
    }
    slow->next=slow->next->next;
    return dummy->next;
}