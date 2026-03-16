#include "core.h"
#include "myclass.h"
#include "mytree.h"

using namespace std;



class Solution
{
public:
    int uniquePaths(int m, int n)
    {
        // dp[i，j]含义到达mat[i，j]的路径数量
        // dp数组初始化：全是0，dp[0,0]=1;
        // 递推顺序：从后往前
        // 递推公式:dp[i,j]=dp[i,j-1]+dp[i-1,j];
        vector<vector<int>> dp(m, vector<int>(n, 0));
        dp[0][0] = 1;
        for (int i = 0; i < m; ++i)
        {
            for (int j = 0; j < n; ++j)
            {
                if (i == 0 && j == 0)
                    continue;
                else
                {
                    if (i == 0)
                        dp[i][j] = dp[i][j - 1];
                    else if (j == 0)
                        dp[i][j] = dp[i - 1][j];
                    else
                        dp[i][j] = dp[i][j - 1] + dp[i - 1][j];
                }
            }
        }
        return dp[m - 1][n - 1];
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