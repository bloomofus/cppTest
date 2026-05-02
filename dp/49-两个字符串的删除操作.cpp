#include "core.h"
#include "utils/myclass.h"
#include "mystruct/mytree.h"

using namespace std;
using namespace mystruct;

class Solution
{
public:
    int minDistance(string word1, string word2)
    {
        // 问题的核心是转换成求两个字符串的最长公共子序列的长度
        int len1 = word1.size(); // word1作为矩阵的侧边，也就是行
        int len2 = word2.size(); // word2作为顶边，列

        vector<vector<int>> dp(len1 + 1, vector<int>(len2 + 1, 0));
        for (int i = 1; i <= len1; ++i)
        {
            for (int j = 1; j <= len2; ++j)
            {
                if (word1[i - 1] == word2[j - 1])
                {
                    // 如果当前对应的行列字符相等，那么dp[i][j]值的意思就是如果字符串比对到word1[i]word2[j]为止
                    // 最长公共子序列长度是dp[i][j]
                    dp[i][j] = dp[i - 1][j - 1] + 1;
                }
                else
                    dp[i][j] = max(dp[i][j - 1], dp[i - 1][j]);
            }
        }
        return len1 + len2 - 2 * dp[len1][len2];
    }
};

int main()
{
    Solution so;
    string str1 = "a";
    string str2 = "b";
    cout << so.minDistance(str1, str2) << endl;
    return 0;
}