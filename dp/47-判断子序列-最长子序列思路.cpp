#include "core.h"
#include "utils/myclass.h"
#include "mystruct/mytree.h"

using namespace std;
using namespace mystruct;

class Solution
{
public:
    bool isSubsequence(string s, string t)
    {
        // 和上上题基本一样，比较一下最长公共子序列和s的长度是否相同即可
        int len1 = s.size();
        int len2 = t.size();
        if (len1 < 1)
            return true;
        if (len2 < 1)
            return false;
        vector<vector<int>> dp(len1, vector(len2, 0));
        for (int i = 0; i < len1; ++i)
        {
            for (int j = 0; j < len2; ++j)
            {
                if (i == 0)
                {
                    if (j == 0)
                        dp[i][j] = s[i] == t[j] ? 1 : 0;
                    else
                        dp[i][j] = max(s[i] == t[j] ? 1 : 0, dp[0][j - 1]);
                }
                else if (j == 0)
                    dp[i][j] = max(s[i] == t[j] ? 1 : 0, dp[i - 1][j]);
                else
                {
                    dp[i][j] = max(max(dp[i - 1][j], dp[i][j - 1]), dp[i - 1][j - 1] + (s[i] == t[j] ? 1 : 0));
                }
            }
        }
        return s.size() == dp[len1 - 1][len2 - 1];
    }
};

int main()
{
    Solution so;
    string str1 = "abc";
    string str2 = "ahbgdc";
    cout << so.isSubsequence(str1, str2) << endl;
}