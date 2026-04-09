#include "core.h"
#include "utils/myclass.h"
#include "mystruct/mytree.h"

using namespace std;

class Solution
{
public:
    int rob(vector<int> &nums)
    {
        // dp[i][0]表示偷到第i家的时候且第i家不偷的最大收益
        // dp[i][1]表示偷到第i家的时候且第i家偷的最大收益，其中i从1~nums.size()
        vector<vector<int>> dp(nums.size() + 1, {0, 0});
        dp[1][0] = 0;
        dp[1][1] = nums[0];
        for (int i = 2; i <= nums.size(); ++i)
        {
            // 开始抢劫到第i家，当前可以抢也可以不抢,i是索引，从1~nums.size()
            // 如果要抢，那么第i-1家一定不能抢，那么收益最大值就是抢到第i-2家的时候（可抢可不抢）的最大收益加上第i家的收益
            // 如果不抢，那么第i-1家，我可以抢也可以不抢，取其最大值，不是第i-1家抢一定比不抢收益多的
            dp[i][1] = max(dp[i - 2][0], dp[i - 2][1]) + nums[i - 1];
            dp[i][0] = max(dp[i - 1][1], dp[i - 1][0]);
        }
        return max(dp[nums.size()][0], dp[nums.size()][1]);
    }
};

class Solution2
{
public:
    int rob(vector<int> &nums)
    {
        //优化版本：实际上一维数组既满足需求
        vector<int> dp(nums.size() + 1, 0);
        //dp[i]含义是偷盗第i家的最大收益，第i家可能偷也可能不偷，i从0~nums.size()
        dp[1] = nums[0];
        for (int i = 2; i <= nums.size();++i)
        {
            dp[i] = max(dp[i - 1], dp[i - 2] + nums[i - 1]);
        }

        return dp[nums.size()];
    }
};

int main()
{
    Solution so;
    vector<int> test{2, 7, 9, 3, 1};
    cout << so.rob(test) << endl;
}