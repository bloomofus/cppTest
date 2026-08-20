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
    ListNode* reverseList(ListNode* head) {
        // -- 思路1:
        // 原来链表的顺序是12345，处理好之后就变成54321，头部变尾部，很容易联想栈数据结构
        // -- 思路2:
        // 也可以直接遍历一遍即可，两两互换
        // 原来是12345，从2开始遍历，处理一次变成21345，再处理一次变成32145
        // 处理可能不是简单互换，仔细观察，发现加一个虚拟头结点就更好处理
        auto way1=[](ListNode* head)-> ListNode* {
            if(!head) return nullptr;
            stack<ListNode*> s{};
            ListNode* cur=head;
            while(cur!=nullptr)
            {
                s.push(cur);
                cur=cur->next;
            }
            ListNode* newHead=s.top();
            while(!s.empty())
            {
                cur=s.top();
                s.pop();
                if(!s.empty())
                    cur->next=s.top();
                else
                    cur->next=nullptr;
            }
            return newHead;
        };
        auto way2=[](ListNode* head)->ListNode* {
            if(!head) return nullptr;
            ListNode dummyHeadNode(0,head);
            auto dummyHead=&dummyHeadNode;
            ListNode* pre=head;
            ListNode* cur=head->next;
            while(cur!=nullptr)
            {
                pre->next=cur->next;
                auto tmp=dummyHead->next;
                dummyHead->next=cur;
                cur->next=tmp;
                cur=pre->next;                
            }
            return dummyHead->next;

        };
        // -- 思路3:
        // 双指针迭代，pre记录前一个节点，cur记录当前节点
        // 每次把cur的next指向pre，然后两个指针同时后移
        // 遍历结束后pre就是新的头节点
        auto way3=[](ListNode* head)->ListNode* {
            ListNode* pre=nullptr;
            ListNode* cur=head;
            while(cur!=nullptr)
            {
                ListNode* tmp=cur->next;
                cur->next=pre;
                pre=cur;
                cur=tmp;
            }
            return pre;
        };
        return way3(head);
    }
};