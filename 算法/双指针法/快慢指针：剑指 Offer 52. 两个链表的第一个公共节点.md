# 快慢指针：[剑指 Offer 52. 两个链表的第一个公共节点](https://leetcode-cn.com/problems/liang-ge-lian-biao-de-di-yi-ge-gong-gong-jie-dian-lcof/)

## 题目描述：

![image-20210721145430578](C:\Users\西安交通大学2193613091sxm\AppData\Roaming\Typora\typora-user-images\image-20210721145430578.png)

## 快慢指针：

```c++
/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode(int x) : val(x), next(NULL) {}
 * };
 */
class Solution {
public:
    ListNode *getIntersectionNode(ListNode *headA, ListNode *headB) {
        //快慢指针
        ListNode*A=headA,*B=headB;
        while(A!=B){
            if(A==nullptr&&B==nullptr)return nullptr;
            A==nullptr?A=headB:A=A->next;
            B==nullptr?B=headA:B=B->next;
        }
        return A;
    }
};
```

