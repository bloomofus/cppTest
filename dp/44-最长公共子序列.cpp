#include "core.h"
#include "utils/myclass.h"
#include "mystruct/mytree.h"

using namespace std;
using namespace mystruct;

class Solution
{
public:
    int longestCommonSubsequence(string text1, string text2)
    {
        // test2作为侧边，text1作为顶边
        // 最核心的方法还是构造一个相等矩阵，然后遍历这个矩阵
        // 这个问题的核心就变成一个矩形区域不相等的行和列其中1的总和最大的数是什么
        // 这就是一个典型的dp问题，和之前的机器人走格子很类似
        // 对于一个目标格子，其有三个来时路，分别是上方，左方和左上方，
        // 当我从左上方来的时候，需要加上当前位置的值，这三个值进行对比取出最大值
        int len1 = text2.size();
        int len2 = text1.size();
        vector<vector<int>> dp(len1, vector(len2, 0));
        for (int i = 0; i < len1; ++i)
        {
            for (int j = 0; j < len2; ++j)
            {
                if (i == 0)
                {
                    if (j == 0)
                        dp[i][j] = text2[i] == text1[j] ? 1 : 0;
                    else
                        dp[i][j] = max(text2[i] == text1[j] ? 1 : 0, dp[0][j - 1]);
                }
                else if (j == 0)
                    dp[i][j] = max(text2[i] == text1[j] ? 1 : 0, dp[i - 1][j]);
                else
                {
                    dp[i][j] = max(max(dp[i - 1][j], dp[i][j - 1]), dp[i - 1][j - 1] + (text2[i] == text1[j] ? 1 : 0));
                }
            }
        }
        return dp[len1 - 1][len2 - 1];
    }
};

int main()
{
    Solution so;
    string str1 = "abcde";
    string str2 = "ace";
    cout << so.longestCommonSubsequence(str1, str2) << endl;
}