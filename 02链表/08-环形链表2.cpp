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
    ListNode *detectCycle(ListNode *head)
    {
        // 这题可以使用hash表来检测入环节点，使用hashmap记录节点与索引，到时候可以直接返回

        unordered_set<ListNode *> set{};
        ListNode *cur = head;
        while (cur != nullptr)
        {
            if (set.find(cur) != set.end())
                return cur;
            else
            {
                set.insert(cur);
                cur = cur->next;
            }
        }
        return nullptr;
    }
};

class Solution2
{
public:
    ListNode *detectCycle(ListNode *head)
    {
        // 通过快慢指针进行遍历，快指针一定会追上慢指针
        // 不过需要注意一些细节，比如初始化的时候fast=head.next，这样避免开局fast==slow
        if (head == nullptr)
            return nullptr;
        ListNode *fast = head->next;
        ListNode *slow = head;
        while (fast != slow)
        {
            if (fast == nullptr || fast->next == nullptr)
            {
                // 没有环
                return nullptr;
            }
            fast = fast->next->next;
            slow = slow->next;
        }
        // 确认有环
        slow = head;
        fast = fast->next;
        while (fast != slow)
        {
            fast = fast->next;
            slow = slow->next;
        }
        return slow;
    }
};

int main()
{
    ListNode *root = new ListNode(1, new ListNode(2, new ListNode(3, new ListNode(4))));
    Solution s;

    return 0;
}