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
        unordered_map<TreeNode *, int> map{};
        // map.reserve(getTreeNodeNum(root));
        // initMap(root, map);

        ;
        return _rob(root, map);
    }

    int _rob(TreeNode *root, unordered_map<TreeNode *, int> &map)
    {
        if (root == nullptr)
            return 0;
        if (map.find(root) == map.end())
            map[root] = 0;
        else
            return map[root];
        // map中没有找到，需要自己去更新
        if (root->left == nullptr && root->right == nullptr)
        {
            // 是叶子结点，需要更新map
            map[root] = root->val;
            return map[root];
        }
        int take = root->val;
        int notake = 0;
        if (root->left)
        {
            take += _rob(root->left->left, map) + _rob(root->left->right, map);
            notake += _rob(root->left, map);
        }
        if (root->right)
        {
            take += _rob(root->right->left, map) + _rob(root->right->right, map);
            notake += _rob(root->right, map);
        }
        map[root] = max(take, notake);
        return map[root];
    }

    int getTreeNodeNum(TreeNode *root)
    {
        if (root == nullptr)
            return 0;
        return 1 + getTreeNodeNum(root->left) + getTreeNodeNum(root->right);
    }

    void initMap(TreeNode *root, unordered_map<TreeNode *, int> &map)
    {
        if (root == nullptr)
            return;
        if (root->left)
        {
            initMap(root->left, map);
        }
        map[root] = 0;
        if (root->right)
        {
            initMap(root->right, map);
        }
    }
};

int main()
{
    Solution so;
    vector<int> test{2, 1, 1, 1};
    TreeNode *root = buildTreeFromOverOrder({3, 4, 5, 1, 3, INT_MIN, 1});
    // cout << so.getTreeNodeNum(root) << endl;
    cout << so.rob(root) << endl;
}