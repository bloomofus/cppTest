#include "core.h"
#include "utils/myclass.h"
#include "mystruct/mytree.h"

using namespace std;
using namespace mystruct;

class Solution
{
public:
    int rob(TreeNode *root)
    {
        // 二叉树后序遍历
        return _rob(root);
    }

    int _rob(TreeNode *root)
    {
        if (root == nullptr)
            return 0;
        // 二叉树后序遍历
        if (root->left == nullptr && root->right == nullptr)
        {
            // 这是一个叶子节点
            return root->val;
        }
        else if (root->left && root->right)
        {
            // 这是一个父节点
            // 父节点偷不偷两种情况，取其收益最大值
            int take = root->val + _rob(root->left->left) + _rob(root->left->right) + _rob(root->right->left) + _rob(root->right->right);
            int noTake = _rob(root->left) + _rob(root->right);
            return max(take, noTake);
        }
        else
        {
            // 只有一个子节点
            TreeNode *child = root->left ? root->left : root->right;
            int take = root->val + _rob(child->left) + _rob(child->right);
            int noTake = _rob(child);
            return max(take, noTake);
        }
        return -1;
    }
};

int main()
{
    Solution so;
    vector<int> test{2, 1, 1, 1};
    TreeNode *root = buildTreeFromOverOrder({3, 4, 5, 1, 3, INT_MIN, 1});
    cout << so.rob(root) << endl;
}