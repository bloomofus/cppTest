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
        // 采用dp思路，将每一天定义为几种状态，每种状态都有一个值，
        // 有几个状态，那么dp数组就是多少维的
        // 第i天的状态：手头没有该股票、手头有该股票
        // dp
        // dp[i][j]含义：第i天状态为j收盘的时候，我的最大利润，j为0，意思是不持有股票
        //           j为1，意为持有股票
        // dp[i][j]初始化：i从0~prices.size()-1,全为0，但dp[0][0]=0;dp[0][1]=-prices[0];
        // 递推公式：
        // 递推方向：i从0~prices.size()-1
        if (prices.size() < 2)
            return 0;
        vector<vector<int>> dp(prices.size(), {0, 0});
        dp[0][1] = -prices[0];
        for (int i = 1; i < prices.size(); ++i)
        {
            // 本来收益为p，今天卖了p+=prices[i]，今天买了，p-=prices[i]，
            //       不操作p+=0
            // dp[i][0]有两种情况：昨天收盘没货今天不操作，昨天收盘有货今天卖了
            dp[i][0] = max(dp[i - 1][0], dp[i - 1][1] + prices[i]);
            // dp[i][1]有两种情况：昨天收盘没货今天买了(由于本题是一次性买卖，所以不是dp[i-1][0]-prices[i])，昨天收盘有货今天不操作
            dp[i][1] = max(-prices[i], dp[i - 1][1]);
        }

        return dp[prices.size() - 1][0];
    }
};

class Solution2
{
public:
    int maxProfit(vector<int> &prices)
    {
        // 由于这个dp数组dp[i]只依赖于dp[i-1]，因此可以压缩dp数组状态
        // dp数组定义：dp[0]为第i天不持有股票的所有收益dp[1]为第i天持有股票的所有收益
        // dp初始化：dp[0]=0,dp[1]=-prices[0]
        // 递推公式：dp[0]=max(dp[0],dp[1]+prices[i]),dp[1]=max(-prices[i],dp[1]);
        // 递推方向:i从1~prices.size()-1
        int len = prices.size();
        if (len < 2)
            return 0;
        int dp[2]{0, -prices[0]};
        for (int i = 1; i < len; ++i)
        {
            int lastDp0 = dp[0];
            int lastDp1 = dp[1];
            dp[0] = max(lastDp0, lastDp1 + prices[i]);
            dp[1] = max(lastDp1, -prices[i]);
        }
        return dp[0];
    }
};

int main()
{
    Solution so;
    vector<int> test{7, 1, 5, 3, 6, 4};
    cout << so.maxProfit(test) << endl;
}