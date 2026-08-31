#include <bits/stdc++.h>
#include "tree.h"
using namespace std;


class Solution {
public:

    // -- 思路:
    // 二叉树后序遍历的顺序是：左 -> 右 -> 中
    // 采用递归实现，定义辅助函数 traversal，每次先递归处理左子树，再递归处理右子树
    // 当左右子树都处理完毕后，最后将当前根节点的值加入结果数组
    auto traversal(TreeNode* root,vector<int>& res)->void
    {
        if(root==nullptr) return; // 递归终止条件：遇到空节点直接返回
        traversal(root->left,res); // 递归遍历左子树
        traversal(root->right,res); // 递归遍历右子树
        res.push_back(root->val); // 将当前节点值加入结果（中）
    }

    vector<int> postorderTraversal(TreeNode* root) {
        vector<int> res{};
        traversal(root,res); // 修复：调用辅助函数 traversal
        return res;
    }
};

class Solution2 {
public:
    // -- 思路:
    // 非递归的方法，所有的递归都可以使用栈来非递归地实现
    // 由于本题是中左右的访问顺序，遍历的顺序就是处理的顺序，直接使用栈既可以
    vector<int> postorderTraversal(TreeNode* root) {
        if(root==nullptr) return {};
        vector<TreeNode*> st{root};
        vector<int> res{};
        while(st.size()>0)
        {
            TreeNode* cur=st.back(); // 取出栈顶节点
            st.pop_back();
            if(cur==nullptr) continue; // 空节点跳过，不处理
            res.push_back(cur->val);   // 中：收集当前节点值
            st.push_back(cur->left);  // 左先入栈（后处理）
            st.push_back(cur->right);   // 右后入栈（先处理）→ 保证 中->右->左 的顺序，最后再翻转
        }
        std::reverse(res.begin(),res.end());
        return res;
    }
};