#include "core.h"
#include "utils/myclass.h"
#include "mystruct/mytree.h"

using namespace std;
using namespace mystruct;

class Solution
{
public:
    vector<int> dailyTemperatures(vector<int> &temperatures)
    {
        // 非常经典的单调栈的题目
        // 我在一开始思维的时候，陷入了一个误区，不是所有的元素都要存在栈里
        // 只需要把必要的元素存起来即可，不需要的直接出栈
        int len = temperatures.size();
        vector<int> res(len, 0);
        stack<int> s{};
        for (int i = 0; i < len; ++i)
        {
            while (!s.empty() && temperatures[s.top()] < temperatures[i])
            {
                res[s.top()] = i - s.top();
                s.pop();
            }
            s.push(i);
        }
        return res;
    }
};
int main()
{
    Solution so;
    string str1 = "aaaaa";
    string str2 = "A";
    vector<int> test{73, 74, 75, 71, 69, 72, 76, 73};
    cout << so.dailyTemperatures(test) << endl;
    return 0;
}