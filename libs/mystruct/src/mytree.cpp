#include "mystruct/mytree.h"
#include <queue>
#include <climits>


namespace mystruct{
    TreeNode *tree::insert(TreeNode *&root, int val)
    {
        if (!root)
            root = new TreeNode(val, nullptr, nullptr);
        else
        {
            if (root->val > val)
                root->left = insert(root->left, val);
            else
                root->right = insert(root->right, val);
        }
        return root;
    }

    void tree::add(int val)
    {
        insert(root, val);
    }

    void tree::preshow(TreeNode *root)
    {
        if (root)
        {
            std::cout << root->val << " ";
            preshow(root->left);
            preshow(root->right);
        }
    }

    void tree::midshow(TreeNode *root)
    {
        if (root)
        {
            midshow(root->left);
            std::cout << root->val << " ";
            midshow(root->right);
        }
    }

    void tree::postshow(TreeNode *root)
    {
        if (root)
        {
            postshow(root->left);
            postshow(root->right);
            std::cout << root->val << " ";
        }
    }

    void tree::overshow(TreeNode *root)
    {
        if (root)
        {
            std::queue<TreeNode *> q;
            q.push(root);
            while (!q.empty())
            {
                int size = q.size();
                std::cout << "[ ";
                for (int i = 0; i < size; ++i)
                {
                    if (q.front()->left)
                        q.push(q.front()->left);
                    if (q.front()->right)
                        q.push(q.front()->right);
                    std::cout << q.front()->val << " ";
                    q.pop();
                }
                std::cout << "] ";
            }
        }
    }

    TreeNode *buildTreeFromOverOrder(std::vector<int> vec)
    {
        // 核心构造的原理是：队列+层序遍历，这里遍历顺序很重要，一定要选择队列，不能是栈
        // 如果vec[i]==INT_MIN，那么视为当前节点不存在
        if (vec.size() == 0)
            return nullptr;
        TreeNode *root = new TreeNode(vec[0], nullptr, nullptr);
        std::queue<TreeNode *> q{};
        q.push(root);
        int idx = 1;
        while (!q.empty() && idx < vec.size())
        {
            TreeNode *nowProcessNode = q.front();
            q.pop();
            // nowProcessNode->val = vec[idx++];
            if (idx < vec.size())
            {
                if (vec[idx] == INT_MIN)
                {
                    // 当前节点不存在
                    nowProcessNode->left == nullptr;
                    ++idx;
                }
                else
                {
                    nowProcessNode->left = new TreeNode(vec[idx++], nullptr, nullptr);
                    q.push(nowProcessNode->left);
                }
            }
            if (idx < vec.size())
            {
                if (vec[idx] == INT_MIN)
                {
                    nowProcessNode->right = nullptr;
                    ++idx;
                }
                else
                {
                    nowProcessNode->right = new TreeNode(vec[idx++], nullptr, nullptr);
                    q.push(nowProcessNode->right);
                }
            }
        }
        return root;
    }
}
    