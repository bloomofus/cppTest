#include "core.h"
#include "utils/myclass.h"
#include "mystruct/mytree.h"

using namespace std;
using namespace mystruct;

class Solution
{
public:
    int maxProfit(vector<int> &prices)
    {
        // 题目只允许两次买卖，因此状态可以分为如下几种：
        //       1，还没持仓，2，第一次买入，3，第一次卖出，4，第二次买入，5，第二次卖出
        //       因此这个dp数组是5维的
        // dp初始化：dp[i][j]全为0，i从0~len-1，dp[0][0]=0,dp[0][1]=-prices[0],
        //  注意这里的初始化，dp[0][2]可以看成当前买了又卖了，所以是0，dp[0][3]就是当天买卖了又买
        // 递推公式：状态j都可以由上一天的j状态和j-1状态推出（j=1,2,3,4)，可以画出状态转换图
        //          dp[i][0]=0,
        //          dp[i][1]=max(-prices[i],dp[i-1][1])
        //          dp[i][2]=max(dp[i-1][1]+prices[i],dp[i-1][2])
        //          dp[i][3]=max(dp[i-1][2]-prices[i],dp[i-1][3])
        //          dp[i][4]=max(dp[i-1][3]+prices[i],dp[i-1][4])
        // 递推方向：i从0~len-1
        int len = prices.size();
        if (len < 2)
            return 0;
        vector<vector<int>> dp(prices.size(), vector<int>(5, 0));
        dp[0][0] = 0;
        dp[0][1] = -prices[0];
        dp[0][2] = 0;
        dp[0][3] = -prices[0];
        dp[0][4] = 0;
        for (int i = 1; i < len; ++i)
        {
            dp[i][0] = 0,
            dp[i][1] = max(-prices[i], dp[i - 1][1]);
            dp[i][2] = max(dp[i - 1][1] + prices[i], dp[i - 1][2]);
            dp[i][3] = max(dp[i - 1][2] - prices[i], dp[i - 1][3]);
            dp[i][4] = max(dp[i - 1][3] + prices[i], dp[i - 1][4]);
        }

        return max3(dp[len - 1][0], dp[len - 1][2], dp[len - 1][4]);
    }

    int max3(int a, int b, int c)
    {
        return max(max(a, b), c);
    }
};

class Solution2
{
public:
    int maxProfit(vector<int> &prices)
    {
        // 优化：压缩dp数组状态
        int len = prices.size();
        if (len < 2)
            return 0;
        int dp[5]{0, -prices[0], 0, -prices[0], 0};
        int lastDpVal[5]{0, -prices[0], 0, -prices[0], 0};
        for (int i = 1; i < len; ++i)
        {
            memcpy(lastDpVal, dp, sizeof(dp));
            dp[0] = lastDpVal[0],
            dp[1] = max(-prices[i], lastDpVal[1]);
            dp[2] = max(lastDpVal[1] + prices[i], lastDpVal[2]);
            dp[3] = max(lastDpVal[2] - prices[i], lastDpVal[3]);
            dp[4] = max(lastDpVal[3] + prices[i], lastDpVal[4]);
        }

        return max(max(dp[0], dp[2]), dp[4]);
    }
};

int main()
{
    Solution so;
    vector<int> test{6, 5, 4, 8, 6, 8, 7, 8, 9, 4, 5};
    cout << so.maxProfit(test) << endl;
}