#include <bits/stdc++.h>
#include "tree.h"
using namespace std;

class Solution {
public:
    bool isSymmetric(TreeNode* root) {
        // -- 思路1:
        // 对称二叉树比较的是根的左子树和右子树是否"镜像相等"
        // 不能只比较左右孩子的值，要一直往下比，所以用递归
        // 递归函数cmp(r1,r2)的含义：以r1和r2为根的两棵子树是否互为镜像
        // 镜像比较规则：r1的左孩子 对应 r2的右孩子，r1的右孩子 对应 r2的左孩子
        // -- 思路2:
        // 也可以用队列/栈迭代：每次取出两个节点，比较值后按"外侧对外侧、内侧对内侧"
        // 的顺序成对入队（left.left配right.right，left.right配right.left），空指针也入队参与判断
        if(!root) return true;
        return cmp(root->left,root->right);
    }

    auto cmp(TreeNode* r1,TreeNode* r2)->bool
    {
        // 空指针判断有三种情况：都空(对称)、一空一非空(不对称)
        if(!r1&&!r2) return true;
        if(!r1&&r2) return false;
        if(r1&&!r2) return false;
        // 下面就是两个都非空：值相等，且"外侧"和"内侧"分别互为镜像
        // 例如树[1,2,2,3,4,4,3]，根的左子树3-4与右子树3-4镜像对应
        return (r1->val==r2->val)&&cmp(r1->left,r2->right)&&cmp(r1->right,r2->left);
    }

    bool isSymmetric2(TreeNode* root) {
        // --思路2:
        // 每一层的首尾的节点如果比较完成，那么可以将其子节点直接按照先后顺序直接加入队列
        if(!root) return true;
        queue<TreeNode*> q{};
        q.push(root->left);
        q.push(root->right); // 先把下一层添加进队列，然后比较这一层是不是对称的
        while(!q.empty())
        {
            int loop=q.size()/2; // 队列里是节点数，每次取出一对，所以要除以2
            for(int i=0;i<loop;++i)
            {
                TreeNode* l=q.front();
                q.pop();
                TreeNode* r=q.front();
                q.pop();
                if(!l&&!r) continue;
                if(l&&!r || !l&&r) return false;
                if(l&&r)
                {
                    if(l->val!=r->val) return false;
                    q.push(l->left);q.push(r->right);
                    q.push(l->right);q.push(r->left); 
                }
            }
        }
        return true;
    }
};