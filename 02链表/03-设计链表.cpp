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

class MyLinkedList
{
public:
    ListNode *head;
    ListNode *tail;
    int size;

    MyLinkedList() : head(nullptr), tail(nullptr), size(0)
    {
    }

    int get(int index)
    {
        if (index < 0)
            return -1;
        ListNode *cur = head;
        while (index--)
        {
            if (cur->next == nullptr)
            {
                // idx是多少，就需要循环多少次
                // 但是在循环的时候cur如果是nullptr，那么就是超出范围了
                return -1;
            }
            else
                cur = cur->next;
        }
        return size == 0 ? -1 : cur->val;
    }

    void addAtHead(int val)
    {
        if (size == 0)
        {
            head = new ListNode(val, nullptr);
            tail = head;
        }
        else
        {
            ListNode *newHead = new ListNode(val, head);
            head = newHead;
        }
        size++;
    }

    void addAtTail(int val)
    {
        if (size == 0)
        {
            head = new ListNode(val, nullptr);
            tail = head;
        }
        else
        {
            tail->next = new ListNode(val, nullptr);
            tail = tail->next;
        }
        size++;
    }

    void addAtIndex(int index, int val)
    {
        if (index < 0 || index > size)
            return;
        else
        {
            // 这个0<=idx<=size范围内,可以统一处理，只有在idx==size的时候cur才有可能为nullptr
            size++;
            ListNode *dummyHead = new ListNode(0, head);
            ListNode *curLast = dummyHead;
            ListNode *cur = head;
            int round = index;
            while (round--)
            {
                // 添加的值在curlast和cur之间
                curLast = cur;
                cur = cur->next;
            }
            curLast->next = new ListNode(val, cur);
            // head、tail处理
            if (size == 1)
            {
                head = curLast->next;
                tail = head;
            }
            else
            {
                head = dummyHead->next;
                if (index + 1 == size)
                {
                    // 插在尾部
                    tail = curLast->next;
                }
            }
        }
    }

    void deleteAtIndex(int index)
    {
        if (index < 0 || index >= size)
            return;
        size--;
        ListNode *dummyHead = new ListNode(0, head);
        ListNode *curLast = dummyHead;
        ListNode *cur = head;
        int round = index;
        while (round--)
        {
            // 删除的值就是cur
            curLast = cur;
            cur = cur->next;
        }
        ListNode *tmpDelete = cur;
        curLast->next = cur->next;
        delete cur;
        // head、tail处理：删除后链表为空、删除后链表长为1、删除头、删除尾
        if (size == 0)
        {
            head = nullptr;
            tail = nullptr;
        }
        else
        {
            head = dummyHead->next;
            if (index == size)
            {
                // 删除尾部
                tail = curLast;
            }
        }
    }
};

int main()
{
    MyLinkedList *obj = new MyLinkedList();
    obj->addAtHead(7);                     
    obj->addAtHead(2);                     
    obj->addAtHead(1);                     
    obj->addAtIndex(3, 0);                 
    obj->deleteAtIndex(2);                 
    obj->addAtHead(6);                     
    obj->addAtTail(4);                     
    obj->get(4);                           
    obj->addAtHead(4);                     
    obj->addAtIndex(5, 0);                 
    obj->addAtHead(6);                     
    return 0;
}