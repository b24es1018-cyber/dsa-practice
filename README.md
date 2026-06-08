# 📘 DSA Practice — Striver's SDE Sheet

Solving Striver's SDE Sheet systematically in **C++**. Tracking progress, patterns, and learnings problem by problem.

---

## 👤 About Me

- **Name:** [Your Name]
- **College:** IIT Jodhpur — B.Tech CSE (3rd Year)
- **Goal:** Placement-ready by December 2025
- **Profile:** [LinkedIn](https://linkedin.com/in/your-profile) • [LeetCode](https://leetcode.com/your-profile)

---

## 📊 Progress

| Topic | Status | Problems Done |
|---|---|---|
| Arrays | ⬜ In Progress | 0 / 24 |
| Linked Lists | ⬜ Not Started | 0 / 18 |
| Binary Search | ⬜ Not Started | 0 / 12 |
| Stacks & Queues | ⬜ Not Started | 0 / 14 |
| Trees | ⬜ Not Started | 0 / 22 |
| BST | ⬜ Not Started | 0 / 14 |
| Graphs | ⬜ Not Started | 0 / 25 |
| Dynamic Programming | ⬜ Not Started | 0 / 50 |
| Greedy | ⬜ Not Started | 0 / 16 |
| Tries | ⬜ Not Started | 0 / 7 |

**Overall: 0% complete (0 / 455)**

> Updated weekly every Sunday.

---

## 📁 Repo Structure

```
dsa-practice/
├── arrays/
│   ├── kadanes_algorithm.cpp
│   ├── two_sum.cpp
│   └── ...
├── linked-lists/
├── binary-search/
├── stacks-queues/
├── trees/
├── bst/
├── graphs/
├── dynamic-programming/
├── greedy/
└── tries/
```

---

## 🧠 How I Approach Each Problem

1. Read the problem — try to solve without hints for **30 minutes**
2. If stuck, look at the approach (not the code)
3. Code the solution from scratch
4. Note the time & space complexity
5. Write the pattern/key insight as a comment at the top of the file

---

## 📌 File Format (every solution)

```cpp
/*
 * Problem : Two Sum
 * Link    : https://leetcode.com/problems/two-sum/
 * Approach: HashMap — store complement while iterating
 * Time    : O(n)
 * Space   : O(n)
 */

#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    vector<int> twoSum(vector<int>& nums, int target) {
        unordered_map<int, int> mp;
        for (int i = 0; i < nums.size(); i++) {
            int complement = target - nums[i];
            if (mp.count(complement)) return {mp[complement], i};
            mp[nums[i]] = i;
        }
        return {};
    }
};
```

---

## 🔑 Key Patterns (updated as I learn)

| Pattern | When to Use |
|---|---|
| Two Pointer | Sorted array, pair/triplet sum problems |
| Sliding Window | Subarray problems with a constraint |
| Prefix Sum | Range sum queries, subarray sum = K |
| Monotonic Stack | Next greater/smaller element |
| BFS | Shortest path in unweighted graph |
| DFS | Connected components, cycle detection |
| Binary Search on Answer | "Minimum maximum" / "Maximum minimum" problems |

---

## 📚 Resources I'm Using

- [Striver's SDE Sheet](https://takeuforward.org/interviews/strivers-sde-sheet-top-coding-interview-problems/)
- [Striver's A2Z DSA Course](https://takeuforward.org/strivers-a2z-dsa-course/strivers-a2z-dsa-course-sheet-2/)
- [NeetCode](https://neetcode.io/) — for visual explanations
- [C++ STL Reference](https://cppreference.com)

---

## ⭐ Star this repo if it helps you too!

