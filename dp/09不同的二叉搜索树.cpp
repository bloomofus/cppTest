#include "core.h"
#include "myclass.h"
#include "mytree.h"

using namespace std;

class Solution
{
public:
    int numTrees(int n)
    {
        // 递推公式：对于n个节点，遍历左子树节点数j从0到i-1，右子树节点数为i-j-1;
        //  拆分之后的左右子树通过调用dp数组里的存储的值，计算乘积（左子树种类*右子树种类），累加更新dp[i];
        //  递推方向：从前往后，后面的需要前面的dp[i];
        //  dp[n]含义：n个不同节点能组成的二叉搜索树的数量;
        //  dp[n]初始化，dp[0]=1,dp[1]=1,dp[2]=2;
        if (n <= 2)
            return n;
        vector<int> dp(n + 1, 0);
        dp[0] = 1;
        dp[1] = 1;
        dp[2] = 2;
        for (int i = 3; i <= n; ++i)
        {
            for (int j = 0; j < i; ++j)
            {
                dp[i] += dp[j] * dp[i - j - 1];
            }
        }
        return dp[n];
    }
};
int main()
{
    Solution so;
    TreeNode *root = nullptr;
    vector<int> test{1, 100, 1, 1, 1, 100, 1, 1, 100, 1};
    vector<vector<int>> test2{vector<int>{0, 0, 0, 0}, vector<int>{0, 0, 0, 1}, vector<int>{0, 0, 1, 0}, vector<int>{0, 0, 0, 0}};
    cout << so.numTrees(3) << endl;
}