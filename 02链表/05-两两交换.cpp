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
    ListNode *swapPairs(ListNode *head)
    {
        // -- 思路
        // 如果使用递归的话会很麻烦，很难返回正确的结果
        // 所以采用dummyhead的方式，使用循环进行控制
        if (head == nullptr)
            return nullptr;
        ListNode dummyHeadNode(0, head);
        ListNode *dummyHead = &dummyHeadNode;
        ListNode *first = head;
        ListNode *second = head->next;
        ListNode *preFirst = dummyHead;
        while (second != nullptr)
        {
            ListNode *afterSecond = second->next;
            preFirst->next = second;
            second->next = first;
            first->next = afterSecond;
            if (afterSecond == nullptr)
            {
                // 退出循环
                break;
            }
            else
            {
                // 更新prefirst、first、second这三个节点
                preFirst = first;
                first = afterSecond;
                second = first->next;
            }
        }
        return dummyHead->next;
    }
};

int main()
{
    ListNode *root = new ListNode(1, new ListNode(2, new ListNode(3, new ListNode(4))));
    Solution s;
    s.swapPairs(root);

    return 0;
}