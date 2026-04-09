#include "core.h"
#include "utils/myclass.h"
#include "mystruct/mytree.h"

using namespace std;

class Solution
{
public:
    int rob(vector<int> &nums)
    {
        // 最核心的思路就是，题目是一个环，但是一个数组的情况好解决，一个环不好解决，
        //      因此，思路就指向，如何把这个环变成一个数组来计算
        // 由于题目是首位相连，那么第一家要么取要么不取，所以直接两种情况并行计算即可
        // 如果第一家取了，那么最后在计算最大值的时候就要注意一下最后一家不能同时取
        // dp[i][0]第一家不取的情况下，偷到第i家时能获取的最大利益
        // dp[i][1]第一家取的情况下，偷到第i家时能获取的最大利益
        if (nums.size() == 1)
            return nums[0];
        vector<vector<int>> dp(nums.size() + 1, {0, 0});
        dp[1][1] = nums[0];
        for (int i = 2; i <= nums.size(); ++i)
        {
            dp[i][0] = max(dp[i - 2][0] + nums[i - 1], dp[i - 1][0]);
            dp[i][1] = max(dp[i - 2][1] + nums[i - 1], dp[i - 1][1]);
        }
        int tmp;
        if (dp[nums.size()][1] == dp[nums.size() - 2][1] + nums[nums.size() - 1])
            tmp = dp[nums.size() - 1][1]; // 注意，判断最后一家偷没偷，如果偷了，就取其前面一个值
        else
            tmp = dp[nums.size()][1];
        for (auto &vec : dp)
        {
            cout << vec[0] << " ";
        }
        cout << endl;
        for (auto &vec : dp)
        {
            cout << vec[1] << " ";
        }
        cout << endl;
        return max(tmp, dp[nums.size()][0]);
    }
};

int main()
{
    Solution so;
    vector<int> test{2, 1, 1, 1};
    cout << so.rob(test) << endl;
}