#include "core.h"
#include "utils/myclass.h"
#include "mystruct/mytree.h"

using namespace std;
using namespace mystruct;

class Solution
{
public:
    int maxSubArray(vector<int> &nums)
    {
        // 我的思路是dp[i]表示以Nums[i]结尾的最大和，最后取dp[i]最值即可
        int len = nums.size();
        if (len < 2)
            return nums[0];
        vector<int> dp(len, 0);
        dp[0] = nums[0];
        int maxNum = nums[0];
        for (int i = 1; i < len; ++i)
        {
            dp[i] = max(dp[i - 1] + nums[i], nums[i]);
            maxNum = max(maxNum, dp[i]);
        }
        return maxNum;
    }
};

int main()
{
    Solution so;
    vector<int> test1{-2, 1, -3, 4, -1, 2, 1, -5, 4};
    cout << so.maxSubArray(test1) << endl;
}