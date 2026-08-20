#include <bits/stdc++.h>
using namespace std;

struct ListNode {
    int val;
    ListNode *next;
    ListNode() : val(0), next(nullptr) {}
    ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode *next) : val(x), next(next) {}
};

class Solution {
public:
    ListNode *getIntersectionNode(ListNode *headA, ListNode *headB) {
        // way1：统计长度差，长链表先走对齐后双指针一起走
        // -- 思路
        // 如果两个链表相交，那么相交之后的部分是共享的
        // 先分别求出两个链表的长度，算出长度之差lenDiff
        // 让长链表的表头先走lenDiff步，使两个链表剩余长度对齐
        // 然后两个表头一起走，直到走到同一个节点，即为相交节点
        auto way1 = [](ListNode *headA, ListNode *headB) -> ListNode * {
            int lenA = 0, lenB = 0;
            ListNode *curA = headA, *curB = headB;
            // 求链表A的长度
            while (curA != nullptr) {
                ++lenA;
                curA = curA->next;
            }
            // 求链表B的长度
            while (curB != nullptr) {
                ++lenB;
                curB = curB->next;
            }
            // 默认让curA指向长链表，curB指向短链表
            curA = headA;
            curB = headB;
            if (lenB > lenA) {
                // 如果B更长，交换角色，保证curA始终指向较长的链表
                swap(lenA, lenB);
                swap(curA, curB);
            }
            // 长链表表头先走长度之差lenDiff步
            int lenDiff = lenA - lenB;
            while (lenDiff--) {
                curA = curA->next;
            }
            // 两个表头一起走，直到相遇或都走到末尾
            while (curA != nullptr && curB != nullptr) {
                if (curA == curB) {
                    // 走到同一个节点，说明找到了相交节点
                    return curA;
                }
                curA = curA->next;
                curB = curB->next;
            }
            // 走到末尾都没有相遇，说明两个链表不相交
            return nullptr;
        };
        // -- 思路2
        // 由于计数的过程有些浪费，所以让两个链表表头一起遍历
        // 长的走完走短的，短的走完走长的
        // 最终都走了长+短这相同的长度距离
        // 如果相交，那么其必定在这个途中相遇
        auto way2 = [](ListNode *headA, ListNode *headB) -> ListNode * {
            auto cur1 = headA;
            auto cur2 = headB;
            // 每步两个指针都向前走一格；走到自己链表末尾就跳到另一条链表头部
            // 这样cur1走A+B、cur2走B+A，总路程相同，相交必在途中相遇
            while (cur1 != cur2) {
                // 走到末尾(为nullptr)说明本段已走完，下一步改走另一条链表
                cur1 = (cur1 == nullptr) ? headB : cur1->next;
                cur2 = (cur2 == nullptr) ? headA : cur2->next;
            }
            // 相遇时cur1==cur2，可能是相交节点，也可能是都走到nullptr(不相交)
            return cur1;
        };
        return way1(headA, headB);
    }
};