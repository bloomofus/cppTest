#include <bits/stdc++.h>
using namespace std;

class Node {
public:
    int val;
    Node* left;
    Node* right;
    Node* next;

    Node(): val(0), left(nullptr), right(nullptr), next(nullptr) {}
    Node(int _val): val(_val), left(nullptr), right(nullptr), next(nullptr) {}
    Node(int _val, Node* _left, Node* _right, Node* _next): val(_val), left(_left), right(_right), next(_next) {}
};

class Solution {
public:
    // 方法1：层序遍历（适用于任意二叉树）
    Node* connect(Node* root) {
        // -- 思路：
        // 层序遍历，每层从左到右把相邻节点用next串起来
        // 比如完全二叉树 [1,2,3,4,5,6,7]，第二层 2->next=3，第三层 4->5->6->7
        // 遍历时记录前一个节点prev，每取出一个节点就把prev->next指向它，然后更新prev
        if(root==nullptr) return nullptr;
        deque<Node*> dq{root};
        while(dq.size()>0)
        {
            int loop=dq.size();
            for(int i=0;i<loop;++i)
            {
                Node* cur=dq.front();
                dq.pop_front();
                if(i!=loop-1) cur->next=dq.front(); 
                if(cur->left) dq.push_back(cur->left);
                if(cur->right) dq.push_back(cur->right);
            }
            // 每层最后一个节点的next默认就是nullptr，不用处理
        }
        return root;
    }

    // 方法2：利用完美二叉树性质（O(1)空间）
    Node* connect2(Node* root) {
        // -- 思路：
        // 利用已连好的 next 指针逐层处理，不需要队列
        // 站在当前层，把下一层的兄弟和堂兄弟连起来
        // 比如当前层 2->3，处理时：2.left->next=2.right, 2.right->next=3.left
        if (!root) return nullptr;
        Node* leftmost = root;
        while (leftmost->left) {
            Node* cur = leftmost;
            while (cur) {
                cur->left->next = cur->right;                    // 同父兄弟
                if (cur->next) cur->right->next = cur->next->left; // 跨父堂兄弟
                cur = cur->next;
            }
            leftmost = leftmost->left; // 移到下一层最左节点
        }
        return root;
    }
};
