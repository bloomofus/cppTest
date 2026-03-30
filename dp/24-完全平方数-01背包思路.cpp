#include "core.h"
#include "myclass.h"
#include "mytree.h"

using namespace std;

class Solution
{
public:
    int numSquares(int n)
    {
        // 本体也还是从集合中取物，使其value总和为某值
        // 但是没有指明集合是什么，就需要自己构造
        // 除非目标为1，否则集合都是1~target/2，而且数量无限，属于完全背包
        // dp[i],总和为i的数字数量最少
        // dp[i]，由于数量取最少，所以初始化为INT_MAX-1，dp[0]=0;(dp[0]不确定之后写代码的时候就确定了)
        // 递推顺序，由于是取组合数，所以先物品，后背包
        // 递推公式,int tmp=dp[bagsize-num*num]+1;if(dp[bagsize]>tmp) dp[bagsize]=tmp;
        if (n == 1)
            return 1;
        vector<int> dp(n + 1, INT_MAX - 10);
        dp[0] = 0;
        for (int i = n / 2; i >= 1; --i)
        {
            int v = i * i;
            for (int bagsize = v; bagsize < n + 1; ++bagsize)
            {
                int tmp = dp[bagsize - v] + 1;
                if (tmp == INT_MAX)
                    continue;
                if (dp[bagsize] > tmp)
                {
                    dp[bagsize] = tmp;
                    cout << dp << endl;
                }
            }
        }
        return dp[n];
    }
};

int main()
{
    Solution so;
    vector<int> test{1, 2, 5};
    cout << so.numSquares(12) << endl;
}