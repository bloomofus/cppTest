#include "core.h"
#include "utils/myclass.h"
#include "mystruct/mytree.h"

using namespace std;

class Solution
{
public:
    bool wordBreak(string s, vector<string> &wordDict)
    {
        //
        // 递推公式：无明显公式，其核心就是看s的前i个能否被字典满足
        // 递推方向：对于背包大小，从小到大遍历背包
        //      遍历背包的子循环遍历物品，看看能否将物品放入
        // dp[i]含义：s的前i+1个字符能否被字典满足
        // dp[i]初始化：全是0

        vector<bool> dp(s.size(), false);
        vector<vector<int>> items{};
        for (auto &word : wordDict)
            items.push_back(getFullStart(s, word));
        for (int i = 0; i < s.size(); ++i)
        {
            // 如果dp[i]==true，不能跳过
            if (dp[s.size() - 1] == true)
                return true;
            for (int j = 0; j < items.size(); ++j)
            {
                for (int k = 0; k < items[j].size(); ++k)
                {
                    if (items[j][k] == i && (i == 0 || dp[i - 1] == true)) // 如果dp初始化为dp(s.size(),false)且qp[0]=true的话，能够优化判断
                    {
                        // 该word和s从s[i]的位置开始相同
                        dp[i + wordDict[j].size() - 1] = true;
                    }
                }
            }
        }
        std::cout << dp << std::endl;
        ;
        return dp[s.size() - 1] == true;
    }

    vector<int> getStart(string &s, string &target)
    {
        // kmp匹配字符串起始位置
        int idx_m = 0;
        int idx_s = 0;
        auto next = getnext(target);
        while (idx_m < s.size() && idx_s < target.size())
        {
            if (s[idx_m] == target[idx_s])
            {
                ++idx_m;
                ++idx_s;
            }
            else if (idx_s == 0)
            {
                // 这里如果不分开讨论，那么会卡在这里循环
                ++idx_m;
            }
            else
            {
                idx_s = next[idx_s];
            }
        }
        if (idx_s == target.size())
            return {idx_m - idx_s};
        return {-1};
    }

    vector<int> getFullStart(string &ms, string &ss)
    {
        // kmp匹配所有起始位置
        int mi = 0;
        int si = 0;
        auto next = getnext(ss);
        vector<int> res{};
        while (mi < ms.size() && si < ss.size())
        {
            if (ms[mi] == ss[si])
            {
                ++mi;
                ++si;
            }
            else if (si == 0)
            {
                ++mi;
            }
            else
            {
                si = next[si];
            }
            if (si == ss.size())
            {
                // 如果匹配到了相等字符串,修改起始位置继续匹配
                res.push_back(mi - si);
                mi = mi - si + 1;
                si = 0;
            }
        }
        return res;
    }

    vector<int> getnext(string &s)
    {
        // next数组的含义就是，当模式字符串和主字符串开始比对时，比对到了s[i]
        // 如果s[i]和main[i]字符不相同，那么s[0~i-1]的最长前缀后缀相等的长度是多少
        // 那么next[i]就是多少，其更现实的含义就是，指向main的遍历索引指向不变
        // 但是指向模式字符串s的索引值变为next[i]，以最大程度利用最后相等的部分
        vector<int> res(s.size(), 0);
        if (s.size() == 0)
            return {};
        else if (s.size() == 1)
            return res;
        res[1] = 0;
        for (int i = 2; i < s.size(); ++i)
        {
            // 最长前缀后缀相等的长度从1~i区间，从大到小开始遍历
            // 因为从小到大会有重复遍历的部分
            // 考虑特殊情况"aab"中的b，这也是i取不到的原因
            // 参考ababc
            for (int j = i - 1; j >= 0; --j)
            {
                bool isEqual{true};
                for (int k = j - 1; k >= 0; --k)
                {
                    if (s[k] != s[i - j + k])
                    {
                        isEqual = false;
                        break;
                    }
                }
                if (isEqual)
                {
                    res[i] = j;
                    break;
                }
            }
        }
        return res;
    }
};

int main()
{
    Solution so;
    string s = "catsandog";
    vector<string> wordDict{"cats", "dog", "sand", "and", "cat"};
    cout << so.wordBreak(s, wordDict) << endl;
}