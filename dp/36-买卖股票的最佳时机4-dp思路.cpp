#include "core.h"
#include "utils/myclass.h"
#include "mystruct/mytree.h"

using namespace std;
using namespace mystruct;

class Solution
{
public:
    int maxProfit(int k, vector<int> &prices)
    {
        // dp数组，状态数量2*k+1
        int len = prices.size();
        if (len < 2)
            return 0;
        vector<vector<int>> dp(len, vector<int>(2 * k + 1, 0));
        for (int i = 0; i < 2 * k + 1; ++i)
        {
            if (i % 2 == 0)
                dp[0][i] = 0;
            else
                dp[0][i] = -prices[0];
        }
        for (int i = 1; i < len; ++i)
        {
            for (int j = 0; j < 2 * k + 1; ++j)
            {
                //状态j只取决于前一天的状态j和前一天的j-1
                if (j == 0)
                    dp[i][j] = dp[i - 1][j];
                else if (j % 2 == 0)
                    dp[i][j] = max(dp[i - 1][j], dp[i - 1][j - 1] + prices[i]);
                else
                    dp[i][j] = max(dp[i - 1][j], dp[i - 1][j - 1] - prices[i]);
            }
        }
        int maxProfit = 0;
        for (int i = 0; i < 2 * k + 1; ++i)
        {
            maxProfit = max(maxProfit, dp[len - 1][i]);
        }

        return maxProfit;
    }
};

int main()
{
    Solution so;
    vector<int> test{6, 5, 4, 8, 6, 8, 7, 8, 9, 4, 5};
    cout << so.maxProfit(2, test) << endl;
}