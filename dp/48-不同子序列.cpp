#include "core.h"
#include "utils/myclass.h"
#include "mystruct/mytree.h"

using namespace std;
using namespace mystruct;

class Solution
{
public:
    int numDistinct(string s, string t)
    {
        // 基本思路还是构造equalMat不变，围绕着这个来做
        // 现在假设s为rbrbt，t为rbt，rbt作为侧边，rbrbt作为顶边
        // 那么dp[i][j]的值,首先如果对应erqualMat格子为0，那么该值需要特殊处理，可能是其dpMat的左边的数字特殊累加，
        //  如果equalMat不为0，就是非同行同列的其左上角区域部分equalMat中的1的总和，（数值上应该是这样，但是更新逻辑不是）
        // 注意，如果两个字符串的字符对比不相等，那么对应的格子必定是0

        // 我这个思路类似于看equalMat找规律
        int len1 = t.size();
        int len2 = s.size();
        vector<vector<long long>> dp(len1, vector<long long>(len2, 0));
        for (int i = 0; i < len1; i++)
        {
            for (int j = 0; j < len2; ++j)
            {
                if (i == 0)
                {
                    // 具体过程是两次遍历当前行
                    // 第一次是更新equalMat，第二次是横向从左到右累积当前数字的所有可能性、
                    // 综合起来就是下面的递推公式
                    if (j == 0)
                        dp[i][j] = (s[j] == t[i] ? 1 : 0);
                    else
                        dp[i][j] = (s[j] == t[i] ? 1 : 0) + dp[i][j - 1];
                }
                else if (j == 0)
                {
                    // 首先如果对应equalMat格子为1，那么其等于左上角区域equalMat中1的总和
                    // 但是该位置没有左上角所以为0
                    dp[i][j] = 0;
                }
                else
                {
                    // 这里也是两轮更新
                    // 第一轮：equalMat格子为1的时候其左上角所有为1的数量
                    //  dp[i][j]=dp[i-1][j-1](相等) dp[i][j]=0(不相等)
                    // 第二轮：累积当前行该字符的所有可能性
                    //  dp[i][j]=dp[i][j-1](不相等) dp[i][j]=dp[i][j]+dp[i][j-1](相等)
                    if (s[j] == t[i])
                    {
                        dp[i][j] = dp[i - 1][j - 1] + dp[i][j - 1];
                    }
                    else
                    {
                        dp[i][j] = dp[i][j - 1];
                    }
                }
            }
        }
        return dp[len1 - 1][len2 - 1];
    }
};

class Solution2
{
public:
    int numDistinct(string s, string t)
    {
        // 优化版：
        // 从经典dp的角度看这个问题
        // 递推公式：
        // 通过两层for循环来实现状态的遍历
        // 对于一个状态，假如s为dpMat顶边，t为dpMat侧边
        // 如果我对比当前对应的字符，如果s[j]==t[i]，说明当前字符相等,当前字符假设为a
        // 那么dp[i][j]就是在遍历到[i][j]这个状态的时候，如果使用a这个字符作为t里面的部分
        // 就只用考虑从a之前的字符里取出字符来组成t字符串里面a字符之前的部分了
        // 那么dp[i][j]可以有dp[i-1][j-1]中组成方法（后面的状态由前面的状态决定）
        // 如果不使用a字符作为t的组成部分，那么就是指，从s的a字符之前取出字符来组成t的一直到a字符的部分
        // 那么就有dp[i][j-1]种方法，
        // 所以if(s[j]==t[i]) dp[i][j]=dp[i-1][j-1]+dp[i][j-1];
        // 那如果s[j]！=t[i]呢，那么就是从s的a字符之前取字符串来组成t里面一直到a字符的部分
        // else dp [i][j]=dp[i][j-1];
        // dp[i][j]含义：从s开头到s[j]字符取字符组成从t[0]到t[i]的方法数量
        // dp[i][j]初始化：i从0~t.size()+1,j从0~s.size()+1,这样初始化是为了后边遍历少一些判断，
        //      dp[0][j]都是1；dp[1~t.size()][0]都是0；(都是举例子反推初始值)
        // 递推方向：i从1~t.size()，j从1~s.size()
        int len1 = t.size();
        int len2 = s.size();
        vector<vector<unsigned long long>> dp(len1 + 1, vector<unsigned long long>(len2 + 1, 0));
        for (int j = 0; j <= len2; ++j)
            dp[0][j] = 1;
        for (int i = 1; i <= len1; ++i)
        {
            for (int j = 1; j <= len2; ++j)
            {
                if (s[j - 1] == t[i - 1])
                    dp[i][j] = dp[i - 1][j - 1] + dp[i][j - 1];
                else
                    dp[i][j] = dp[i][j - 1];
            }
        }
        // cout << dp << endl;
        return dp[len1][len2];
    }
};

int main()
{
    Solution2 so;
    string str1 = "babgbag";
    string str2 = "bag";
    cout << so.numDistinct(str1, str2) << endl;
}