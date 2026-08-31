#include <bits/stdc++.h>
#include "tree.h"
using namespace std;

class Solution {
public:
    // -- 思路:
    // 标准的二叉树层序遍历（BFS）。
    // 借助普通单向队列 queue 逐层遍历。
    // 每次 while 开始时，通过队列当前大小 (loopNum) 锁定这一层的节点数，
    // 例如树是 [3,9,20,null,null,15,7]：
    // 初始队列 [3]，loopNum=1，弹出3，将9和20入队，当前层收集到 [3]；
    // 下一轮队列 [9,20]，loopNum=2，依次弹出9和20，将15和7入队，当前层收集到 [9,20]；
    // 依此类推，直到队列清空，res 就包含了每一层的节点值。
    vector<vector<int>> levelOrder(TreeNode* root) {
        vector<vector<int>> res{};
        if (root == nullptr) return res; // 边界情况：空树直接返回

        queue<TreeNode*> q; 
        q.push(root); 
        
        while (!q.empty()) {
            int loopNum = q.size();      // 锁定当前层的节点数量
            vector<int> tmpV{};
            tmpV.reserve(loopNum);       // 提前分配内存，避免多次动态扩容
            
            for (int i = 0; i < loopNum; ++i) {
                auto node = q.front();
                q.pop();
                tmpV.push_back(node->val); // 收集当前节点值

                // 左右子节点按顺序入队，作为下一层的数据
                if (node->left) q.push(node->left);
                if (node->right) q.push(node->right);
            }
            res.push_back(tmpV); // 将处理完的当前层存入结果集
        }
        return res;
    }
};
