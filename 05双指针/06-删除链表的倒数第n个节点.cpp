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
    ListNode* removeNthFromEnd(ListNode* head, int n) {
        // -- 思路:
        // 删除倒数第n个节点，最直观的方法是先遍历一遍算长度，再遍历一遍定位目标节点，需要两次遍历
        // 优化：用快慢指针只遍历一次，让快指针先走n步，然后快慢指针同时前进
        // 当快指针到达链表末尾时，慢指针刚好指向倒数第n个节点
        // 为了方便处理删除头节点的边界情况，加一个虚拟头节点，记录slow的前驱便于删除
        if(!head) return nullptr;
        ListNode dummyHeadNode(0,head);
        auto dummyHead=&dummyHeadNode;
        auto f=head;
        auto s=dummyHead;
        n--;
        while(n--)
        {
            f=f->next;
        }
        while(f->next!=nullptr)
        {
            f=f->next;
            s=s->next;
        }
        // 循环结束之后，s的下一个位置就是要删除的节点
        auto tmp=s->next->next;
        delete s->next;
        s->next=tmp;
        return dummyHead->next;
    }
};