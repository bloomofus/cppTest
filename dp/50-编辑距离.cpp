#include "core.h"
#include "utils/myclass.h"
#include "mystruct/mytree.h"

using namespace std;
using namespace mystruct;

void call(int x = 0)
{
    std::cout << "call from " << x << std::endl;
}

class Solution
{
public:
    // 这道题的核心是认识到操作字符串a和操作字符串b是等价的，比如说让字符串a增加一个字符
    //  等于让字符串b删除一个字符，
    //  而且千万不要想着去找矩阵里的变化规律，只用把矩阵作为一个思维的参考即可
    //  通过矩阵我们可以认识到有三个方向可以接近dp[i][j]
    // 当比较到dp[i][j]的时候，如果对应位置的字符相等，那么dp[i][j]=dp[i-1][j-1]
    //          就相当于i-1长度的字串a和j-1长度的字串b变相等的操作数
    // 如果对应位置的字符不相等，那么就需要通过操作，让其变得相等，总的来说，
    // 有三个起点，dp[i-1][j-1]、dp[i-1][j]、dp[i][j-1]
    // 操作有三个，也可以说是两个，因为加减都是一样的，
    // 通过操作，能够帮我们从起点状态到达目标状态dp[i][j]
    // 如果从dp[i-1][j-1]到达目标状态，由于最新的比较字符不相等，通过替换一次操作即可，总操作数为dp[i-1][j-1]+1;
    // 如果从dp[i-1][j]开始，就是删除侧边最新的那个字符，总操作数为dp[i-1][j]+1
    // 如果从dp[i][j-1]开始，就是删除最新的顶边的那个字符，总操作数为dp[i][j-1]+1
    int minDistance(string word1, string word2)
    {
        int len1 = word2.size();
        int len2 = word1.size();
        if (len1 < 1)
            return len2;
        if (len2 < 1)
            return len1;
        vector<vector<int>> dp(len1, vector<int>(len2, 0));
        // dp初始化
        dp[0][0] = (word1[0] == word2[0] ? 0 : 1);
        bool isUsed = (dp[0][0] == 0 ? true : false);
        for (int j = 1; j < len2; ++j)
        {
            // 第一行初始化
            if (!isUsed && word2[0] == word1[j])
            {
                dp[0][j] = dp[0][j - 1];
                isUsed = true;
            }
            else
            {
                dp[0][j] = dp[0][j - 1] + 1;
            }
        }
        isUsed = (dp[0][0] == 0 ? true : false);
        for (int i = 1; i < len1; ++i)
        {
            // 第一列初始化
            if (!isUsed && word2[i] == word1[0])
            {
                dp[i][0] = dp[i - 1][0];
                isUsed = true;
            }
            else
            {
                dp[i][0] = dp[i - 1][0] + 1;
            }
        }
        cout << dp << endl;
        for (int i = 1; i < len1; ++i)
        {
            for (int j = 1; j < len2; ++j)
            {
                if (word2[i] == word1[j])
                {
                    dp[i][j] = dp[i - 1][j - 1];
                }
                else
                {
                    dp[i][j] = min(dp[i - 1][j - 1], min(dp[i][j - 1], dp[i - 1][j])) + 1;
                }
            }
        }
        cout << dp << endl;
        return dp[len1 - 1][len2 - 1];
    }
};

int main()
{
    Solution so;
    string str1 = "AA";
    string str2 = "A";
    cout << so.minDistance(str1, str2) << endl;
    return 0;
}