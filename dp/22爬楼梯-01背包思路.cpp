#include "core.h"
#include "myclass.h"
#include "mytree.h"

using namespace std;

class Solution
{
public:
    int climbStairs(int n)
    {
        // 物品集合为1和2，背包的最大容量就是n
        // 于是本体可以看成是从物品集合中取出，装满背包容量有多少种方法
        // dp[i]含义，到达i楼层有多少种方法
        // dp[i]初始化，dp[0]=1,意思是我什么也不取这种方式能够使背包总容量为0，其余为0
        // 递推顺序，先背包后物品集合，因为是排列问题而不是组合问题，
        // 递推公式，if(nums[j]<=i) dp[i]+=dp[i-nums[j]]; nums:1,2
        vector<int> dp(n + 1, 0);
        dp[0] = 1;
        for (int i = 0; i < n + 1; ++i)
        {
            for (int j = 1; j < 3; ++j)
            {
                if (j <= i)
                    dp[i] += dp[i - j];
            }
        }
        return dp[n];
    }
};

int main()
{
    Solution so;
    vector<int> test{1, 2, 3};

    cout << so.climbStairs(3) << endl;
}