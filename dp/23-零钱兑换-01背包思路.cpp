#include "core.h"
#include "myclass.h"
#include "mytree.h"

using namespace std;



//可以看出，先背包后物品效率更高
class Solution1
{
public:
    int coinChange(vector<int> &coins, int amount)
    {
        // 从集合中取物是典型的01背包问题特征
        // dp[i]含义，总和为i的最少硬币数量
        // dp[i]都是INT_MAX-10,dp[0]=0;(根据写代码的时候的递推公式得出)，为什么要减去10，是因为可能会溢出
        // 递推顺序，先背包后集合，而且遍历集合的时候先挑大的遍历
        //       或者先将物品集合倒序排序，然后先遍历物品再遍历背包亦可
        // 递推公式,int tmp=dp[bagsize-coin_value]+1;if(tmp<dp[bagsize]) dp[bagsize]=tmp;
        vector<int> dp(amount + 1, INT_MAX - 10);
        dp[0] = 0;
        std::sort(coins.begin(), coins.end(), [](int a, int b)
                  { return a > b; });
        // cout << coins << endl;
        for (int i = 0; i < coins.size(); ++i)
        {
            int v = coins[i];
            for (int bagsize = v; bagsize <= amount; ++bagsize)
            {
                int tmp = dp[bagsize - v] + 1; // 取当前物品的coins数量
                if (dp[bagsize] > tmp)
                {
                    dp[bagsize] = tmp;
                    cout << dp << endl;
                }
            }
        }
        cout << dp << endl;
        return dp[amount] == INT_MAX - 10 ? -1 : dp[amount];
    }
};

class Solution2
{
public:
    int coinChange(vector<int> &coins, int amount)
    {
        // 先背包后物品的思路
        vector<int> dp(amount + 1, INT_MAX - 10);
        dp[0] = 0;
        std::sort(coins.begin(), coins.end(), [](int a, int b)
                  { return a > b; });
        for (int bagsize = 0; bagsize < amount + 1; ++bagsize)
        {
            for (int i = 0; i < coins.size(); ++i)
            {
                int v = coins[i];
                if (v <= bagsize)
                {
                    int tmp = dp[bagsize - v] + 1;
                    if (tmp < dp[bagsize])
                        dp[bagsize] = tmp;
                }
            }
        };
        cout << dp << endl;
        return dp[amount] == INT_MAX - 10 ? -1 : dp[amount];
    }
};

int main()
{
    Solution2 so;
    vector<int> test{1, 2, 5};
    cout << so.coinChange(test, 11) << endl;
}