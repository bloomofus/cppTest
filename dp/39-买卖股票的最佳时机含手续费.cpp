#include "core.h"
#include "utils/myclass.h"
#include "mystruct/mytree.h"

using namespace std;
using namespace mystruct;

class Solution
{
public:
    int maxProfit(vector<int> &prices, int fee)
    {
        // 区别就在于状态转换的时候是否需要手续费
        // 状态转移如下：没买->没买，没买->买了，买了->买了，买了->卖了，卖了->卖了，卖了->买了
        int len = prices.size();
        if (len < 2)
            return 0;
        int dp[3]{0, -prices[0] - fee, 0};
        int lastDpVal[3]{0, -prices[0] - fee, 0};
        for (int i = 1; i < len; ++i)
        {
            memcpy(lastDpVal, dp, sizeof(dp));
            dp[0] = lastDpVal[0];
            dp[1] = max3(lastDpVal[0] - prices[i] - fee, lastDpVal[1], lastDpVal[2] - prices[i] - fee);
            dp[2] = max(lastDpVal[2], lastDpVal[1] + prices[i]);
        }
        return max(dp[0], dp[2]);
    }

    int max3(int a, int b, int c)
    {
        return max(max(a, b), c);
    }
};

int main()
{
    Solution so;
    vector<int> test{1, 3, 2, 8, 4, 9};
    cout << so.maxProfit(test, 2) << endl;
}