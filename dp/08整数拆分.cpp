#include "core.h"
#include "myclass.h"
#include "mytree.h"

using namespace std;

class Solution
{
public:
    int integerBreak(int n)
    {
        // 递推公式：对于要拆分的数n，需要将其从1到其一半进行遍历拆分;
        //  拆分之后的两个数通过调用dp数组里的存储的值，计算乘积，取其最大值更新dp[n];
        //  递推方向：从前往后，后面的需要前面的dp[i];
        //  dp[n]含义：n可以拆分的乘积最大值;
        //  dp[n]初始化，dp[1]=1,dp[2]=1;
        vector<int> dp(n + 1, 0);
        dp[1] = 1;
        dp[2] = 1;
        if (n <= 2)
            return 1;
        for (int i = 3; i <= n; ++i)
        {
            for (int j = 1; j < i / 2 + 1; ++j)
            {
                dp[i] = max(max(dp[j], j) * max(dp[i - j], i - j), dp[i]);
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
    cout << so.integerBreak(8) << endl;
}