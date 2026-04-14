#include "core.h"
#include "utils/myclass.h"
#include "mystruct/mytree.h"

using namespace std;
using namespace mystruct;

class Solution
{
public:
    int lengthOfLIS(vector<int> &nums)
    {
        // 这道题使用dp的难点在于：怎么去构造状态
        // 首先，我知道是构造一个dp(len,0)，但是这个dp[i]的值是什么
        // 按道理来说应该是遍历到第i个数字时候的一个状态值
        // 一直遍历到最后一个数字去填充这个dp数组
        // 但是难点就在于如果dp[i]表示遍历到第i个数字的最长子序列的话
        // 那么dp[i+1]很难由dp[i]推导，两者很难构成依赖关系
        // 因此巧妙的一点在于将dp[i]定义为以nums[i]结尾的子序列最长长度
        // 这样就可以将dp[i+1]与dp[i~0]进行关联起来
        // 最后返回的时候需要遍历返回最大值
        int len = nums.size();
        vector<int> dp(len, 0);
        dp[0] = 1;
        for (int i = 1; i < nums.size(); ++i)
        {
            dp[i] = 1;
            for (int j = i - 1; j >= 0; --j)
            {
                if (nums[i] > nums[j])
                    dp[i] = max(1 + dp[j], dp[i]);
            }
        }
        int maxLen = 0;
        for (int j = len - 1; j >= 0; --j)
        {
            maxLen = max(maxLen, dp[j]);
        }
        return maxLen;
    }
};

class Solution2
{
public:
    int lengthOfLIS(vector<int> &nums)
    {
        // 优化版
        int len = nums.size();
        int maxLen = 1;
        vector<int> dp(len, 1);
        for (int i = 1; i < nums.size(); ++i)
        {
            for (int j = i - 1; j >= 0; --j)
            {
                if (nums[i] > nums[j])
                    dp[i] = max(1 + dp[j], dp[i]);
            }
            maxLen = max(maxLen, dp[i]);
        }
        return maxLen;
    }
};

int main()
{
    Solution so;
    vector<int> test{1, 2, 3};
    cout << so.lengthOfLIS(test) << endl;
}