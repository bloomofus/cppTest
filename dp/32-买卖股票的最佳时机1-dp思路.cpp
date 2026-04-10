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
        // 由于只能买卖一次，所以dp策略就是使用dp[i]表示第i天能够获取的最大利润
        //   而且我必须记录下曾经的最小成本，这样到一个新的卖点的时候，我才能知道一个新的利润是多少
        //  dp[i]含义：在第i天不管卖不卖，获得的最大利润，i范围0~prices.size()-1
        //  dp[i]初始化：全是0
        //  递推公式：dp[i]=max(dp[i-1],prices[i]-minCost)，max参数1意思是第i天之前就完成了买卖操作获取了最大的利润
        //           max参数2的含义就是，在最低成本买，在第i天卖掉，那么我获取的利润最大，以这次买卖操作更新旧的买卖操作
        //  递推顺序：遍历每一天
        if (prices.size() < 2)
            return 0;
        vector<int> dp(prices.size(), 0);
        int minCost = prices[0];
        for (int i = 1; i < prices.size(); ++i)
        {
            // i范围：0~prices.size()-1
            dp[i] = max(dp[i - 1], prices[i] - minCost);
            minCost = min(minCost, prices[i]);
        }
        return dp[prices.size() - 1];
    }
};

class Solution2
{
public:
    int maxProfit(vector<int> &prices)
    {
        // 优化版本，由于dp数组只使用到上一个值，所以dp数组可以压缩成一个值。
        if (prices.size() < 2)
            return 0;
        int maxProfit = 0;
        int minCost = prices[0];
        for (int i = 1; i < prices.size(); ++i)
        {
            // i范围：0~prices.size()-1
            maxProfit = max(maxProfit, prices[i] - minCost);
            minCost = min(minCost, prices[i]);
        }
        return maxProfit;
    }
};

int main()
{
    Solution so;
    vector<int> test{2, 1, 2, 0, 1};
    cout << so.maxProfit(test) << endl;
}