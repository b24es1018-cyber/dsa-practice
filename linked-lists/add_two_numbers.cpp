//Initialize a dummy node as a new node
        ListNode *dummy = new ListNode(); 
        ListNode *temp = dummy; 
        //Carry will be carried to the next new node created
        int carry = 0;
        //Iterate till the end of both the lists
        while( (l1 != NULL || l2 != NULL) || carry) {
            int sum = 0; 
            if(l1 != NULL) {
                sum += l1->val; 
                l1 = l1 -> next; 
            }
            //Repeat the same process for l2 as l1
            if(l2 != NULL) {
                sum += l2 -> val; 
                l2 = l2 -> next; 
            }
            //Carry gets added to sum in the node (carry=sum/10)
            sum += carry; 
            carry = sum / 10; 
            ListNode *node = new ListNode(sum % 10); 
            temp -> next = node; 
            temp = temp -> next; 
        }
        return dummy -> next; 