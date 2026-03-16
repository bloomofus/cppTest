#include "core.h"
#include "myclass.h"
#include "mytree.h"

using namespace std;

class Solution
{
public:
    int minCostClimbingStairs(vector<int> &cost)
    {
        // 递推公式：dp[n]=min(dp[n-1]+cost[n-1],dp[n-2]+cost[n-2]);
        // 遍历顺序：从后往前；
        // dp初始化：dp[0]=dp[1]=0;
        // dp[n]含义：到第n个阶梯需要的最小力气；
        vector<int> dp(cost.size() + 1, 0);
        int n = 2;
        while (n <= cost.size())
        {
            dp[n] = min(dp[n - 1] + cost[n - 1], dp[n - 2] + cost[n - 2]);
            ++n;
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
    cout << so.minCostClimbingStairs(test) << endl;
    // std::cout<< so.reconstructQueue(tmp) << std::endl;
    // printMatrixStyle(input_data);
}