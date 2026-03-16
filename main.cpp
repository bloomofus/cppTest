#include "core.h"
#include "myclass.h"
#include "mytree.h"

using namespace std;

class Solution
{
public:
    int integerBreak(int n)
    {
    }
};
int main()
{
    Solution so;
    TreeNode *root = nullptr;
    vector<int> test{1, 100, 1, 1, 1, 100, 1, 1, 100, 1};
    vector<vector<int>> test2{vector<int>{0, 0, 0,0},vector<int>{0,0,0,1},vector<int>{0,0,1,0},vector<int>{0,0,0,0}};
    cout << so.integerBreak(10) << endl;
}