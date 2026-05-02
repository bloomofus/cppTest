#include "core.h"
#include "utils/myclass.h"
#include "mystruct/mytree.h"

using namespace std;
using namespace mystruct;

class Solution
{
public:
    int longestPalindromeSubseq(string s)
    {
        // 这道题的思路还是和上一道题类似
        // 上一道题求是否是回文字串，那么dp[l][r]就只由dp[l+1][r-1]这一个状态推导出来
        // 但是这道题的话是最长回文子序列，中间l+1到r-1的部分可以删除部分，
        // 而且也可能l到r无法都利用拓展回文子序列
        // 反而l或r也可以和l+1到r-1的部分组成回文子序列
        // 所以dp[l][r]这个状态可以由dp[l+1][r-1]、dp[l][r-1]、dp[l+1][r]这三个状态推出来
        // 如果s[l]==s[r]说明加上l和r的字符可以拓展从l+1到r-1的部分
        // 如果不相等，那么，可以先利用一边看看最长回文子序列是多少，然后取其最大值
        // 由于遍历的顺序，后面三个状态都会在dp[l][r]之前得出结果

        int len = s.size();
        vector<vector<int>> dp(len, vector<int>(len, 0));
        for (int i = len - 1; i >= 0; --i)
        {
            for (int j = i; j < len; ++j)
            {
                if (i == j)
                {
                    dp[i][j] = 1;
                }
                else if (j == i + 1)
                {
                    if (s[i] == s[j])
                        dp[i][j] = 2;
                    else
                        dp[i][j] = 1;
                }
                else
                {
                    if (s[i] == s[j])
                    {
                        dp[i][j] = dp[i + 1][j - 1] + 2;
                    }
                    else
                    {
                        dp[i][j] = max(dp[i][j - 1], dp[i + 1][j]);
                    }
                }
            }
        }
        return dp[0][len - 1];
    }
};
int main()
{
    Solution so;
    string str1 = "aaaaa";
    string str2 = "A";
    cout << so.longestPalindromeSubseq(str1) << endl;
    return 0;
}