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
    ListNode *detectCycle(ListNode *head) {
        // -- 思路:
        // 快慢指针（Floyd 判圈算法），分两步解决
        // 第一步判断是否有环：f 每次走 2 步，s 每次走 1 步
        // 如果有环，两者速度不同必相遇；如果无环，f 会先走到链表尾（f->next 或 f->next->next 为空）
        // 第二步找入环点：设头到入环点距离为 a，入环点到相遇点为 b，环剩余长度为 c（环长 b+c）
        // 相遇时 s 走了 a+b，f 走了 a+b+n(b+c)，又 f 速度是 s 的两倍，整理得 a = (n-1)(b+c)+c
        // 含义：头到入环点的距离 == 相遇点再走 c 步绕回入环点
        // 所以让一个指针从开头（dummyHead）出发，另一个留在相遇点，两者同速各走 1 步
        // 再次相遇之处，就是环的入点
        auto dummyHeadNode=ListNode(0,head);
        auto dummyHead=&dummyHeadNode;
        auto f=dummyHead;
        auto s=dummyHead;
        while(1)
        {
            if(f->next==nullptr||f->next->next==nullptr)
            {
                // f指针走到头了，结果还没遇到s指针，所以没有环
                return nullptr;
            }
            f=f->next->next;
            s=s->next;
            if(f==s) break;
        }
        // 在这里f和s相遇了
        // 需要两个速度一样的指针，一个从开头出发，一个从相遇之处出发
        // 再相遇之处就是环的入点
        s=dummyHead;
        while(f!=s)
        {
            f=f->next;
            s=s->next;
        }
        return f;
    }
};