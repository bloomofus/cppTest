#include "core.h"
#include "utils/myclass.h"
#include "mystruct/mytree.h"

using namespace std;
using namespace mystruct;

class Solution
{
public:
    int findLength(vector<int> &nums1, vector<int> &nums2)
    {
        // 通过一个二维矩阵表示两个数组的数字是否相同
        int len1 = nums1.size();
        int len2 = nums2.size();
        vector<vector<int>> equalMat(len2, vector(len1, 0));
        vector<vector<int>> dp(len2, vector(len1, 0));
        for (int i = 0; i < len2; ++i)
        {
            for (int j = 0; j < len1; ++j)
                if (nums2[i] == nums1[j])
                    equalMat[i][j] = 1;
        }
        cout << equalMat << endl;
        int maxLen = 0;
        for (int i = 0; i < len2; ++i)
        {
            for (int j = 0; j < len1; ++j)
            {
                if (i == 0 || j == 0)
                {
                    dp[i][j] = equalMat[i][j];
                }
                else
                {
                    if (equalMat[i - 1][j - 1] == 0)
                        dp[i][j] = equalMat[i][j];
                    else if (equalMat[i][j] == 1)
                        dp[i][j] = dp[i - 1][j - 1] + 1;
                    else
                        dp[i][j] = 0;
                }
                maxLen = max(maxLen, dp[i][j]);
            }
        }
        cout << dp << endl;
        return maxLen;
    }
};

class Solution2
{
public:
    int findLength(vector<int> &nums1, vector<int> &nums2)
    {
        // 优化版：减少了一个二维数组
        int len1 = nums1.size();
        int len2 = nums2.size();
        vector<vector<int>> dp(len2, vector(len1, 0));
        for (int i = 0; i < len2; ++i)
        {
            for (int j = 0; j < len1; ++j)
                if (nums2[i] == nums1[j])
                    dp[i][j] = 1;
        }
        cout << dp << endl;
        int maxLen = 0;
        for (int i = 0; i < len2; ++i)
        {
            for (int j = 0; j < len1; ++j)
            {
                if (i > 0 && j > 0)
                {
                    if (dp[i][j] == 1)
                        dp[i][j] = dp[i - 1][j - 1] + 1;
                }
                maxLen = max(maxLen, dp[i][j]);
            }
        }
        cout << dp << endl;
        return maxLen;
    }
};

class Solution3
{
public:
    int findLength(vector<int> &nums1, vector<int> &nums2)
    {
        // 更加优化版：减少了一个循环
        int len1 = nums1.size();
        int len2 = nums2.size();
        vector<vector<int>> dp(len2, vector(len1, 0));
        int maxLen = 0;
        for (int i = 0; i < len2; ++i)
        {
            for (int j = 0; j < len1; ++j)
            {
                if (nums2[i] == nums1[j])
                    dp[i][j] = 1;
                if (i > 0 && j > 0)
                {
                    if (dp[i][j] == 1)
                        dp[i][j] = dp[i - 1][j - 1] + 1;
                }
                maxLen = max(maxLen, dp[i][j]);
            }
        }
        cout << dp << endl;
        return maxLen;
    }
};

int main()
{
    Solution3 so;
    vector<int> test{1, 1, 0, 0, 1, 1};
    vector<int> test2{0, 0};
    cout << so.findLength(test, test2) << endl;
}