#include "core.h"
#include "myclass.h"
#include "mytree.h"

using namespace std;

class Solution
{
public:
    int findMaxForm(vector<string> &strs, int m, int n)
    {
        // 将每个字符串变为一个vector<int>{m,n}，这样输入就变为了一些数字对
        // 要求所有的m和n都不超过目标
        // 那么我就遍历这个数字对，逐渐实现各个dp
        // dp[m,n]表示不超过mn的最大字符串数量
        // 将不加当前数字对的dp值和加上当前数字对的总和对比，看看需不需要更新dp
        // 于是递推公式就是dp+=(dp[j-arr[i][0]][k-arr[i][1]]+1>dp[j][k])?1:0;

        // 优化建议：01字符串不需要预先整理成二维数组，遍历的时候处理即可
        vector<vector<int>> arr(strs.size(), vector<int>(2, 0));
        for (int i = 0; i < arr.size(); ++i)
        {
            for (auto num : strs[i])
            {
                if (num == '0')
                    ++arr[i][0];
                if (num == '1')
                    ++arr[i][1];
            }
        }
        vector<vector<int>> dp(m + 1, vector<int>(n + 1, 0));
        for (int i = 0; i < arr.size(); ++i)
        {
            for (int j = m; j >= arr[i][0]; --j)
            {
                for (int k = n; k >= arr[i][1]; --k)
                {
                    if (dp[j - arr[i][0]][k - arr[i][1]] + 1 > dp[j][k])
                        ++dp[j][k];
                }
            }
        }
        return dp[m][n];
    }
};

int main()
{
    Solution so;
    vector<string> test{"10", "0001", "111001", "1", "0"};
    cout << so.findMaxForm(test, 5, 3) << endl;
}