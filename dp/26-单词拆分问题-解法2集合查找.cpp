#include "core.h"
#include "utils/myclass.h"
#include "mystruct/mytree.h"

using namespace std;

class Solution
{
public:
    bool wordBreak(string s, vector<string> &wordDict)
    {
        // 通过将字典转换为set减少查询时间
        // 递推公式：无明显公式，其核心就是看s的前i个能否被字典满足
        // 递推方向：对于背包大小，从小到大遍历背包
        //      遍历背包的子循环遍历物品，看看能否将物品放入
        // dp[i]含义：s的前i个字符能否被字典满足
        // dp[i]初始化：全是0，且dp[0]=1;
        set<string> wordSet{};
        for (auto &wordStr : wordDict)
            wordSet.insert(wordStr);
        vector<bool> dp(s.size() + 1, false);
        dp[0] = true;
        string subStr{};
        for (int i = 0; i <= s.size(); ++i)
        {
            // dp[i]是指s前i个子字符组成的字符串能否被字典满足
            for (int j = i; j < s.size(); ++j)
            {
                // j是指截取字符串的起始位置索引
                subStr = s.substr(i, j - i + 1);
                if (dp[i] == true && wordSet.find(subStr) != wordSet.end())
                    dp[j + 1] = true; // 这里索引千万别搞混
            }
        }
        return dp[s.size()];
    }
};

int main()
{
    Solution so;
    string s = "leetcode";
    vector<string> wordDict{"leet", "coode"};
    cout << so.wordBreak(s, wordDict) << endl;
}