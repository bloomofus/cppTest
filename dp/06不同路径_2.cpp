#include "core.h"
#include "myclass.h"
#include "mytree.h"

using namespace std;

class Solution
{
public:
    int uniquePaths(int m, int n)
    {
        //其原理就在于逐行模拟发现dp数组可以压缩
        // 创建一维DP数组，表示到达每一列的路径数
        vector<int> dp(n, 1);

        // 从第二行开始更新
        for (int i = 1; i < m; i++)
        {
            // 对于每一列，路径数 = 上方路径数 + 左方路径数
            for (int j = 1; j < n; j++)
            {
                dp[j] += dp[j - 1];
            }
        }

        return dp[n - 1];
    }
};

int main()
{
    Solution so;
    TreeNode *root = nullptr;
    vector<int> test{1, 100, 1, 1, 1, 100, 1, 1, 100, 1};
    vector<int> test2{10, 15, 20};
    cout << so.uniquePaths(2, 3) << endl;
    // std::cout<< so.reconstructQueue(tmp) << std::endl;
    // printMatrixStyle(input_data);
}