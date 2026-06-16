/**
first copy next value to current node
then point nodenext to nodenextnext 
so that both have same values node and node next
now store the nodenext to temp and delete
 */
class Solution {
public:
struct Node {
    int data;
    Node* next;
    Node(int val) {
        data = val;
        next = NULL;
    }
};
    void deleteNode(ListNode* node) {
        node->val = node->next->val;

        ListNode* temp = node->next;
        node->next = node->next->next;

        delete temp;
    }
};