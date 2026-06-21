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
    ListNode *reverseList(ListNode *head)
    {
        // -- 思路
        // 这个算法的核心就是原来的head的下一个元素，将其删除，然后将其加到dummyhead的后边
        if (head == nullptr)
            return nullptr;
        ListNode *dummyHead = new ListNode(0, head);
        ListNode *cur = head->next;
        head->next = nullptr;
        while (cur != nullptr)
        {
            ListNode *curNext = cur->next;
            cur->next = dummyHead->next;
            dummyHead->next = cur;
            cur = curNext;
        }
        ListNode *newHead = dummyHead->next;
        delete dummyHead;
        return newHead;
    }
};

class Solution2
{
public:
    ListNode *reverseList(ListNode *head)
    {
        // -- 思路
        // 这个算法的核心就是不断遍历这个链表，原来的指向是A->B，更改之后是B->A，
        // 需要注意B的后续节点和A的上游节点的存储
        ListNode *dummyHead = nullptr;
        ListNode *curLast = dummyHead; // 遍历之后，cur->curLast变成新的头节点
        ListNode *cur = head;
        while (cur != nullptr)
        {
            ListNode *curNext = cur->next; // 这个是新的cur节点，cur和curNext的相对关系不变
            // 由于是不断需要将往后的指向变成往前的指向的，所以在循环之前curLast的指向应该是往前的，而cur的指向是往后的
            // 所以循环就是需要把cur的指向变成往前的，以及更新cur与curLast
            cur->next = curLast;
            curLast = cur;
            cur = curNext;
        }
        return curLast;
    }
};

class Solution3
{
public:
    ListNode *reverseList(ListNode *head)
    {
        // -- 思路
        // 递归法，如果输入就是一个链表的话，那么最值的递归结束条件就是链表里面只有一个元素，那么我返回值无论是头节点还是尾节点
        // 都是不合适的，很难解决问题
        // 所以，需要输入两个链表，一个是指向前面的链表，一个是指向后边的链表，最后返回的指向前面的链表的头节点
        std::function<ListNode *(ListNode *, ListNode *)> reverse;
        reverse = [&reverse](ListNode *frontHead, ListNode *nextHead) -> ListNode *
        {
            if(nextHead==nullptr){
                // 结束条件
                return frontHead;
            }
            ListNode *newNextHead = nextHead->next;
            nextHead->next = frontHead;
            frontHead = nextHead;
            nextHead = newNextHead;
            return reverse(frontHead,nextHead);
        };

        ListNode *frontHead = nullptr;
        ListNode *nextHead = head;

        return reverse(frontHead,nextHead);
    }
    
};

int main()
{

    return 0;
}