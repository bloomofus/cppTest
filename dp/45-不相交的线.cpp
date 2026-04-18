#include "core.h"
#include "utils/myclass.h"
#include "mystruct/mytree.h"

using namespace std;
using namespace mystruct;

class Solution
{
public:
    int maxUncrossedLines(vector<int> &nums1, vector<int> &nums2)
    {
        // 这道题和上一道题类似，基本思路也是求不同行不同列的1的数量之和
        // 而且天然是有序的，不会相交
        // 本质是求最长公共子序列
        int len1 = nums1.size();
        int len2 = nums2.size();
        vector<vector<int>> dp(len1, vector(len2, 0));
        for (int i = 0; i < len1; ++i)
        {
            for (int j = 0; j < len2; ++j)
            {
                if (i == 0)
                {
                    if (j == 0)
                        dp[i][j] = nums1[i] == nums2[j] ? 1 : 0;
                    else
                        dp[i][j] = max(dp[i][j - 1], nums1[i] == nums2[j] ? 1 : 0);
                }
                else if (j == 0)
                    dp[i][j] = max(dp[i - 1][j], nums1[i] == nums2[j] ? 1 : 0);
                else
                {
                    dp[i][j] = max(max(dp[i][j - 1], dp[i - 1][j]), dp[i - 1][j - 1] + (nums1[i] == nums2[j] ? 1 : 0));
                }
            }
        }
        return dp[len1 - 1][len2 - 1];
    }
};

int main()
{
    Solution so;
    vector<int> test1{2, 5, 1, 2, 5};
    vector<int> test2{10, 5, 2, 1, 5, 2};
    cout << so.maxUncrossedLines(test1, test2) << endl;
}