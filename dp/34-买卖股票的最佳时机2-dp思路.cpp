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
        // 这题也可以沿用之前的dp思路
        // 我记录下之前的最小成本，并且不断记录着最大利润，
        // 当我最大利润不再为0，意思就是我有了一个不错的买点卖点，
        // 但是还需要判断卖点是否还会继续走高，也就是最大利润是否会继续上涨
        // 当最大利润不再继续上涨，直到其下跌，意思就是该次买卖已经结束了
        // 所以最大利润在可能下跌的那一天，那一天就是最新的最低成本点，开始搜寻新一个卖点
        if (prices.size() < 2)
            return 0;
        vector<int> dp(prices.size(), 0); // 一次买卖称为一次持仓，dp[i]表示当前持仓的累计收益
        int minCost = prices[0];
        int sumProfit = 0;
        for (int i = 1; i < prices.size(); ++i)
        {
            if (dp[i - 1] <= prices[i] - minCost)
            {
                // 第i天是比之前更好的卖点，或者同样不错的卖点
                dp[i] = prices[i] - minCost;
            }
            else
            {
                // 之前的买卖操作已经完成，第i天不是更好的卖点，是新一轮的可能最低买点
                sumProfit += dp[i - 1];
                dp[i] = 0;
                minCost = prices[i];
            }
        }
        // 防止最后一天之前连涨导致sumProfit没有加上最后一次持仓的收益
        return sumProfit + (dp[prices.size() - 1] == 0 ? 0 : dp[prices.size() - 1]);
    }
};

int main()
{
    Solution so;
    vector<int> test{7, 1, 5, 3, 6, 4};
    cout << so.maxProfit(test) << endl;
}