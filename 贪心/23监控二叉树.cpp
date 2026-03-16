#include "core.h"
#include "myclass.h"
#include "mytree.h"

using namespace std;

void printMatrixStyle(const std::vector<std::vector<int>> &vec);
vector<vector<int>> sortIntervals(vector<vector<int>> &intervals);

class Solution
{
public:
    int minCameraCover(TreeNode *root)
    {
        int sum = 0;
        recurse(root, nullptr, sum);
        return sum;
    }

    void recurse(TreeNode *root, TreeNode *father, int &sum)
    {
        if (root == nullptr)
            return;
        recurse(root->left, root, sum);
        recurse(root->right, root, sum);
        sum += _process(root, father);
    }

    int _process(TreeNode *root, TreeNode *father)
    {
        // val:
        // 1:当前有监控
        // 2:当前被监控
        if (root == nullptr)
            return 0;
        if (root->val == 1)
            return 0;
        if (root->left == nullptr && root->right == nullptr)
        {
            if (father == nullptr)
                return 1;
            if (father->val != 1)
            {
                father->val = 1;
                root->val = 2;
                return 1;
            }
            else
            {
                root->val = 2;
                return 0;
            }
        }
        else if (root->left && root->right)
        {
            // 按理来说，由于后序遍历，不存在子节点没有被照到的情况，只用看子节点有没有监控即可
            if (root->left->val == 1 || root->right->val == 1)
            {
                root->val = 2;
            }
            else
            {
                if (father)
                {
                    if (father->val != 1)
                    {
                        father->val = 1;
                        root->val = 2;
                        return 1;
                    }
                    else
                    {
                        root->val = 2;
                        return 0;
                    }
                }
                else
                {
                    root->val = 1;
                }
                return 1;
            }
        }
        else
        {
            TreeNode *child = root->left ? root->left : root->right;
            if (child->val == 1)
                root->val = 2;
            else if (child->val == 2)
            {
                if (father)
                {
                    if (father->val != 1)
                    {
                        father->val = 1;
                        root->val = 2;
                        return 1;
                    }
                    else
                    {
                        root->val = 2;
                        return 0;
                    }
                }
                else
                {
                    root->val = 1;
                }
                return 1;
            }
            // else{
            //     root->val = 1;
            //     child->val = 2;
            // }
        }
        return 0;
    }
};

int main()
{
    Solution so;
    TreeNode *root = nullptr;
    cout << so.minCameraCover(nullptr) << endl;
    // std::cout<< so.reconstructQueue(tmp) << std::endl;
    // printMatrixStyle(input_data);
}