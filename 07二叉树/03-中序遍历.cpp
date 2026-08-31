#include <bits/stdc++.h>
#include "tree.h"
using namespace std;

class Solution {
public:
    // -- 思路:
    // 二叉树中序遍历的顺序是：左 -> 中 -> 右
    // 采用递归实现，先递归左子树，再访问当前节点，最后递归右子树
    auto traversal(TreeNode* root, vector<int>& res) -> void
    {
        if (root == nullptr) return; // 递归终止条件
        traversal(root->left, res);  // 左
        res.push_back(root->val);    // 中
        traversal(root->right, res); // 右
    }

    vector<int> inorderTraversal(TreeNode* root) {
        vector<int> res{};
        traversal(root, res);
        return res;
    }
};


class Solution2 { // 非递归的版本
public:
    vector<int> inorderTraversal(TreeNode* root) {
        // -- 思路
        // 二叉树一共就是4种遍历。前中后层序，还有2种实现方法，递归和循环
        // 循环里面，bfs是队列，dfs是栈
        // 这里的核心思路就是通过一个栈和cur指针，
        // 就是说给我一个cur节点，如果cur不是空，如果他有左子节点
        // 那么就要把当前节点加入st，左子节点设置为cur
        // 如果左子节点是null的时候，那么就需要处理当前节点，然后将右子节点加入st，（右子节点不是null)
        // 然后像之前的节点一样，查找右子节点的左子节点是否存在，
        // 如果在上一步cur的左子节点是null，右子节点也是null，那么就需要持续处理栈里的值
        // 直到栈里有一个值的右子节点不是null，然后将其设置为cur
        if(root==nullptr) return {};
        vector<int> res{};
        stack<TreeNode*> st;
        TreeNode* cur=root;
        while(cur!=nullptr || st.size()>0)
        {
            if(cur->left!=nullptr)
            {
                st.push(cur);
                cur=cur->left;
            }
            else
            {
                res.push_back(cur->val);
                if(cur->right==nullptr)
                {
                    cur=nullptr;
                    while(st.size()>0)
                    {
                        auto curNode=st.top();
                        st.pop();
                        res.push_back(curNode->val);
                        if(curNode->right!=nullptr)
                        {
                            cur=curNode->right;
                            break;
                        }
                    }
                }
                else cur=cur->right;
            }
        }
        return res;
    }
};


class Solution3 { // 统一风格的非递归的版本
public:
    vector<int> inorderTraversal(TreeNode* root) {
        // -- 思路:
        // 统一风格的核心技巧：用一个 nullptr 作为"标记"插入栈中
        // 当从栈顶取出一个非空节点时，说明它还没被"访问"过
        //   我们就把它按中序的逆序重新入栈：右 -> 自己 -> nullptr -> 左
        //   nullptr 插在"自己"和"左"之间，表示：nullptr 后面紧跟的那个节点是要被记录到结果的
        // 当从栈顶取出 nullptr 时，说明标记后面的节点已经被处理完左子树了
        //   此时弹出 nullptr，再弹出紧跟的节点，把它的值加入结果
        //
        // 举个例子，树:
        //     1
        //      \
        //       2
        //      /
        //     3
        // 中序应该是 1 -> 3 -> 2
        //
        // 初始: st=[1]
        // 第1轮: 取出1(非空), 逆序入栈 → st=[右2, 1, null]  (1没有左孩子)
        // 第2轮: 取出null → 弹null, 弹1, res=[1]  → st=[右2]
        // 第3轮: 取出2(非空), 逆序入栈 → st=[右null跳过, 2, null, 左3] → st=[2, null, 3]
        // 第4轮: 取出3(非空), 无左右 → st=[2, null, 3, null]  (3没有左右孩子, 只入3和null)
        //         实际: pop3, push3, push null → st=[2, null, 3, null]
        // 第5轮: 取出null → 弹null, 弹3, res=[1,3]  → st=[2, null]
        // 第6轮: 取出null → 弹null, 弹2, res=[1,3,2]  → st=[]
        // 结束。结果 [1,3,2] ✓
        if(root==nullptr) return {};
        vector<int> res{};
        stack<TreeNode*> st;
        st.push(root);
        while(st.size()>0)
        {
            auto cur=st.top();
            if(cur!=nullptr)
            {
                st.pop(); // 先把当前节点弹出来，后面要按逆序重新入栈
                if(cur->right) st.push(cur->right); // 右子节点先入（最后处理）
                st.push(cur);     // 当前节点重新入栈
                st.push(nullptr); // nullptr 标记：表示紧跟其后的节点需要被记录到结果
                if(cur->left) st.push(cur->left); // 左子节点最后入（最先处理）
            }
            else
            {
                // 遇到 nullptr，说明标记后面的节点已经处理完毕（左子树都遍历过了）
                st.pop();            // 弹出 nullptr 标记
                cur=st.top();        // 取出真正要处理的节点
                st.pop();
                res.push_back(cur->val); // 记录结果
            }
        }        
        return res;
    }
};