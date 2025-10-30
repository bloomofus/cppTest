#include "core.h"
#include "myclass.h"
#include "mytree.h"

using namespace std;

class Solution
{
public:
    vector<string> binaryTreePaths(TreeNode *root)
    {
    }
};

int main()
{
    Solution so;
    vector<int> nums = {3, 1, 0, 8, 4, 2,9,7 };
    tree t;
    for (auto i : nums)
    {
        t.add(i);
    }
    // t.overshow(t.root);
    TreeNode *rootl = new TreeNode(2,nullptr,nullptr);
    TreeNode *rootr = new TreeNode(3, nullptr, nullptr);
    TreeNode *root = new TreeNode(1,rootl,rootr);
    cout << so.binaryTreePaths(t.root);
}