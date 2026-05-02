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
    int countSubstrings(string s)
    {
        int len = s.size();
        int sum = 1;
        for (int i = 1; i < len; ++i)
        {
            int num = 1;
            for (int j = 0; j < i; ++j)
            {
                if (isLoop(s.substr(i - j - 1, j + 2)))
                {
                    // cout << s.substr(i - j - 1, j + 2) << endl;
                    ++num;
                }
            }
            sum += num;
        }
        // cout << dp << endl;
        return sum;
    }

    bool isLoop(string s)
    {
        int l = 0;
        int r = s.size() - 1;
        while (l < r)
        {
            if (s[l] == s[r])
            {
                ++l;
                --r;
            }
            else
                break;
        }
        if (r == l || s[l] == s[r])
            return true;
        else
            return false;
    }
};
int main()
{
    Solution so;
    string str1 = "aaa";
    string str2 = "A";
    cout << so.countSubstrings(str1) << endl;
    return 0;
}