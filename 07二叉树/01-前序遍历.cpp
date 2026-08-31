#include <bits/stdc++.h>
#include "tree.h"
using namespace std;

class Solution {
public:
    // -- 思路:
    // 前序遍历顺序：中 -> 左 -> 右。
    // 提取辅助函数 traversal 并将 res 作为局部变量传递，避免类成员变量在多次调用时发生结果累加。
    void traversal(TreeNode* cur, vector<int>& res) {
        if (cur == nullptr) return; // 递归终止条件：遇到空节点直接返回
        res.push_back(cur->val);    // 中：收集当前节点值
        traversal(cur->left, res);  // 左：递归遍历左子树
        traversal(cur->right, res); // 右：递归遍历右子树
    }

    vector<int> preorderTraversal(TreeNode* root) {
        vector<int> res;
        traversal(root, res);
        return res;
    }
};


class Solution2 {
public:
    // -- 思路:
    // 非递归的方法，所有的递归都可以使用栈来非递归地实现
    // 由于本题是中左右的访问顺序，遍历的顺序就是处理的顺序，直接使用栈既可以
    vector<int> preorderTraversal(TreeNode* root) {
        if(root==nullptr) return {};
        vector<TreeNode*> st{root};
        vector<int> res{};
        while(st.size()>0)
        {
            TreeNode* cur=st.back(); // 取出栈顶节点
            st.pop_back();
            if(cur==nullptr) continue; // 空节点跳过，不处理
            res.push_back(cur->val);   // 中：收集当前节点值
            st.push_back(cur->right);  // 右先入栈（后处理）
            st.push_back(cur->left);   // 左后入栈（先处理）→ 保证 中->左->右 的顺序
        }
        return res;
    }
    // 前序和后序的非递归写法是同一套模板：出栈后立即处理节点，再按相反顺序压入子节点。
    // 后序只需把前序的压栈顺序反过来（先左后右），最后把结果翻转即可得到 左->右->中。
    // 而中序不同：访问顺序是 左->中->右，"访问"和"处理"的顺序不一致——
    // 节点出栈后不能立刻处理，必须先用指针一路向左走到底，再回头处理，
    // 所以中序的非递归需要一个额外的 cur 指针配合栈来实现。
};

