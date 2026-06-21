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
    ListNode *removeNthFromEnd(ListNode *head, int n)
    {
        // -- 思路
        // 最快的方法就是只遍历一次，遍历到结尾只能发现有多少个元素
        // 要想删除倒数第n个节点，还得遍历一次
        // 但是可以设置一个小跟班，当主指针到达结尾的时候，副指针刚好到达要删除的节点
        ListNode *fast = head;
        ListNode *slow = head;
        for (int i = 0; i < n - 1; ++i)
        {
            // 快指针先走
            if (fast == nullptr)
            {
                return head; // 说明n输入不合理
            }
            fast = fast->next;
        }
        // 快慢指针一起走
        ListNode dummyHeadNode(0, head);
        ListNode *preSlow = &dummyHeadNode;
        while (fast->next != nullptr)
        {
            fast = fast->next;
            preSlow = slow;
            slow = slow->next;
        }
        // 删除慢指针所在节点
        preSlow->next = slow->next;
        delete slow;
        return dummyHeadNode.next;
    }
};

int main()
{
    ListNode *root = new ListNode(1, new ListNode(2, new ListNode(3, new ListNode(4))));
    Solution s;

    return 0;
}