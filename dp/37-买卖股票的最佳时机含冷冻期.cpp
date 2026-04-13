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
        // 题目说是有冷冻期，实际上就是加了一个冷冻的状态
        //  状态转移：没买->没买,没买->买了，买了->买了，买了->卖了，卖了->冷冻
        //       冷冻->冷冻，冷冻->买了
        int len = prices.size();
        if (len < 2)
            return 0;
        // dp[0]没买dp[1]买了dp[2]卖了dp[3]冷冻
        int dp[4]{0, -prices[0], 0, 0};
        int lastDpVal[4]{0, -prices[0], 0, 0};
        for (int i = 1; i < len; ++i)
        {
            memcpy(lastDpVal, dp, sizeof(dp));
            dp[0] = lastDpVal[0];
            dp[1] = max3(lastDpVal[0] - prices[i], lastDpVal[3] - prices[i], lastDpVal[1]);
            dp[2] = lastDpVal[1] + prices[i];
            dp[3] = max(lastDpVal[3], lastDpVal[2]);
        }

        return max3(dp[0], dp[2], dp[3]);
    }

    int max3(int a, int b, int c)
    {
        int tmp = max(a, b);
        return max(tmp, c);
    }
};

int main()
{
    Solution so;
    vector<int> test{1, 2, 4};
    cout << so.maxProfit(test) << endl;
}