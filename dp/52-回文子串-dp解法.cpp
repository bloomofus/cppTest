#include "core.h"
#include "utils/myclass.h"
#include "mystruct/mytree.h"

using namespace std;
using namespace mystruct;

class Solution
{
public:
    int countSubstrings(string s)
    {
        // 这道题我本来的思路是dp[l][r]作为字符串l开始r结尾的字串的回文子串的数量
        // 但是当状态转移的时候，对于之前的状态，利用的很少，
        // 比如，dp[l][r]由dp[l+1][r-1]、dp[l][r-1]、dp[l+1][r]三个状态转移而来
        // 但是转移到目标状态的时候，不好求递推公式，还是只能遍历一次，损失很大效率，只比纯暴力好一点点
        // 所以，当这个思路不好做的时候，要想想思路是不是错了
        // 是否需要将问题转化一下，将问题转化为字符串l开始r结尾的子串是不是回文串
        // 如果这样转换，那么当我进行递推的时候，很明显能够使用之前的状态
        // dp还是一个二维数组，dp[l][r]表示字符串l开始r结尾的子串是不是回文串
        // 递推方向是l从len-1~0，而r则是从l~len-1，
        // 递推的核心是，字符串l开始r结尾的子串，如果s[l]==s[r]，那么如果字符串l+1开始r-1结尾的子串也是回文串
        //      那么，字符串l开始r结尾的子串就是回文串，否则不是
        // 回文串的数量在遍历的时候顺手累加即可
        int len = s.size();
        vector<vector<bool>> dp(len, vector<bool>(len, false));
        int sum = 0;
        for (int l = len - 1; l >= 0; --l)
        {
            for (int r = l; r < len; ++r)
            {
                if (l == r)
                {
                    dp[l][r] = true;
                }
                else if (r == l + 1)
                {
                    dp[l][r] = (s[l] == s[r]);
                }
                else
                {
                    dp[l][r] = (s[l] == s[r] && dp[l + 1][r - 1]);
                }
                if (dp[l][r])
                    ++sum;
            }
        }
        cout << dp << endl;
        return sum;
    }
};
int main()
{
    Solution so;
    string str1 = "aaaaa";
    string str2 = "A";
    cout << so.countSubstrings(str1) << endl;
    return 0;
}