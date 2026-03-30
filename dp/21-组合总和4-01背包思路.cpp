#include "core.h"
#include "myclass.h"
#include "mytree.h"

using namespace std;

class Solution
{
public:
    int combinationSum4(vector<int> &nums, int target)
    {
        // 思路参考上一篇解题思路，关于先遍历背包还是先遍历物品的顺序的讲解
        vector<unsigned long long> dp(target + 1, 0);
        dp[0] = 1;

        for (int i = 0; i < target + 1; ++i)
        {
            for (int j = 0; j < nums.size(); ++j)
            {
                if (nums[j] <= i)
                {
                    dp[i] += dp[i - nums[j]];
                    // cout << dp << endl;
                }
            }
        }
        return dp[target];
    }
};

int main()
{
    Solution so;
    vector<int> test{1, 2, 3};

    cout << so.combinationSum4(test, 4) << endl;
}