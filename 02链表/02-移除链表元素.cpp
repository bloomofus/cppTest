#include <bits/stdc++.h>
using namespace std;

struct ListNode
{
    int val;
    ListNode *next;
    ListNode() : val(0), next(nullptr) {};
    ListNode(int x) : val(x), next(nullptr) {};
    ListNode(int x, ListNode *next) : val(x), next(next) {};
};

class Solution
{
public:
    ListNode *removeElements(ListNode *head, int val)
    {
        ListNode *dummyHead = new ListNode(0, head);
        ListNode *cur = dummyHead;
        while (cur->next != nullptr)
        {
            ListNode *u = cur;
            ListNode *v = cur->next;
            if (v->val == val)
            {
                // 需要删除下游节点v
                u->next = v->next;
                delete v;
            }
            else
            {
                // 不需要删除下游节点
                cur = v;
            }
        }
        ListNode *res = dummyHead->next;
        delete dummyHead;
        return res;
    }
};
int main()
{
    Solution so;

    return 0;
}