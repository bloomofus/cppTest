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
    ListNode *getIntersectionNode(ListNode *headA, ListNode *headB)
    {
        // -- 思路
        // 最简单是用哈希
        // 还有一种思路就是比较链表长度大小，通过双指针让其相遇，通过比较链表长度大小，让长的链表指针先出发，避免多余判断
        auto way1 = [&]() -> ListNode *
        {
            // 哈希
            ListNode *curA = headA;
            unordered_set<ListNode *> set{};
            while (curA != nullptr)
            {
                set.insert(curA);
                curA = curA->next;
            }
            ListNode *curB = headB;
            while (curB != nullptr)
            {
                if (set.find(curB) != set.end())
                {
                    return curB;
                }
                else
                    curB = curB->next;
            }
            return nullptr;
        };

        auto way2 = [&]() -> ListNode *
        {
            // 双指针
            int listAlen = 0;
            ListNode *curA = headA;
            while (curA != nullptr)
            {
                listAlen++;
                curA = curA->next;
            }
            int listBlen = 0;
            ListNode *curB = headB;
            while (curB != nullptr)
            {
                listBlen++;
                curB = curB->next;
            }
            ListNode *longOne;
            ListNode *shortOne;
            longOne = (listAlen >= listBlen ? headA : headB);
            shortOne = (listAlen >= listBlen ? headB : headA);
            ListNode *curLong = longOne;
            ListNode *curShort = shortOne;
            int diff = abs(listAlen - listBlen);
            while (diff--)
            {
                curLong = curLong->next;
            }
            while (curLong != curShort)
            {
                curLong = curLong->next;
                curShort = curShort->next;
            }
            return curLong;
        };

        return way2();
    }
};

int main()
{
    ListNode *root = new ListNode(1, new ListNode(2, new ListNode(3, new ListNode(4))));
    Solution s;

    return 0;
}