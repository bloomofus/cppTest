#include "core.h"
#include "myclass.h"
#include "mytree.h"

using namespace std;

class Solution
{
public:
    int uniquePathsWithObstacles(vector<vector<int>> &obstacleGrid)
    {
        // 递推公式：如果当前位置有障碍，那么dp[i][j]=0,否则dp[i][j]=dp[i-1][j]+dp[i][j-1];
        // 递推方向：从前往后
        //
        vector<vector<int>> dp(obstacleGrid.size(), vector<int>(obstacleGrid[0].size(), 1));
        for (int i = 0; i < dp.size(); ++i)
        {
            for (int j = 0; j < dp[0].size(); ++j)
            {
                if (obstacleGrid[i][j] == 1)
                {
                    dp[i][j] = 0;
                    continue;
                }
                if (i + j == 0)
                    continue;

                if (i == 0)
                {
                    dp[i][j] = dp[i][j - 1] == 0 ? 0 : dp[i][j - 1];
                }
                else if (j == 0)
                {
                    dp[i][j] = dp[i - 1][j] == 0 ? 0 : dp[i - 1][j];
                }
                else
                {
                    dp[i][j] = dp[i - 1][j] + dp[i][j - 1];
                }
            }
        }
        return dp[dp.size() - 1][dp[0].size() - 1];
    }
};

int main()
{
    Solution so;
    TreeNode *root = nullptr;
    vector<int> test{1, 100, 1, 1, 1, 100, 1, 1, 100, 1};
    vector<vector<int>> test2{vector<int>{0, 0, 0, 0}, vector<int>{0, 0, 0, 1}, vector<int>{0, 0, 1, 0}, vector<int>{0, 0, 0, 0}};
    cout << so.uniquePathsWithObstacles(test2) << endl;
}