/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode() : val(0), next(nullptr) {}
 *     ListNode(int x) : val(x), next(nullptr) {}
 *     ListNode(int x, ListNode *next) : val(x), next(next) {}
 * };
 */
class Solution {
public:
    ListNode* reverseList(ListNode* head) {
        // Initialize previous pointer to NULL
        ListNode* prev = NULL;

        // Start from the head of the list
        ListNode* temp = head;

        // Traverse the list
        while (temp != NULL) {
            // Save the next node
            ListNode* front = temp->next;

            // Reverse the current node's pointer
            temp->next = prev;

            // Move prev to current node
            prev = temp;

            // Move to the next node
            temp = front;
        }

        // Return new head (last node becomes first)
        return prev;
    }
    };
