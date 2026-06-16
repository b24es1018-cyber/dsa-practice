/*
create a map and store the address and check if it repeats
*/
#include <bits/stdc++.h>
using namespace std;
    bool hasCycle(ListNode *head) {
        ListNode* temp = head;

        unordered_map<ListNode*, int> nodeMap;

        while (temp != nullptr) {
            if (nodeMap.find(temp) != nodeMap.end()) {
                return true;
            }

            nodeMap[temp] = 1;
            temp = temp->next;
        }

        return false;
    }
};