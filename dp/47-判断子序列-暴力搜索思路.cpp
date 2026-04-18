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
        // 暴力搜索
        int len1 = s.size();
        int len2 = t.size();
        int startIdx = 0;
        int equalLen = 0;
        for (int i = 0; i < len1; ++i)
        {
            for (int j = startIdx; j < len2; ++j)
            {
                if (s[i] == t[j])
                {
                    startIdx = j + 1;
                    ++equalLen;
                    break;
                }
            }
        }
        return len1 == equalLen;
    }
};

int main()
{
    Solution so;
    string str1 = "abc";
    string str2 = "ahbgdc";
    cout << so.isSubsequence(str1, str2) << endl;
}