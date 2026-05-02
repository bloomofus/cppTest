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
        // 从前往后遍历每一个字符，然后对这些字符从中心往左右拓展
        int sum = 0;
        vector<int> dp(s.size(), 0);
        for (int i = 0; i < s.size(); ++i)
        {
            int tmp = sum;
            bool lastEqual = true;
            for (int j = 0; j <= i; ++j)
            {
                // 对应字符为中心向外拓展
                if (s[i - j] == s[i + j] && lastEqual)
                    ++sum;
                else
                    break;
            }
            if (i + 1 < s.size() && s[i] == s[i + 1])
            {
                lastEqual = true;
                for (int j = 0; j <= i; ++j)
                {
                    // 对应两个字符为中心向外拓展
                    if (s[i - j] == s[i + 1 + j] && lastEqual)
                        ++sum;
                    else
                        break;
                }
            }
            dp[i] = (sum - tmp);
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