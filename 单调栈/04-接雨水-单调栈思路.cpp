#include "core.h"
#include "utils/myclass.h"
#include "mystruct/mytree.h"

using namespace std;
using namespace mystruct;

#define print

class Solution
{
public:
    int trap(vector<int> &height)
    {
        // 题目要求的是所有深V的雨水之和，因此求解思路有两个
        // 首先就是直观的纵向求解，典型的就是dp思路这个方法
        // 其次就是横向求解，这个很难想，具体的做法就是对每一个柱子进行遍历
        // 然后看其左边第一个比它大的柱子和右边第一个比他大的柱子
        // 看起来似乎要先求两个单调栈记录结果，实际上安排好比较的思路，一个单调栈即可
        // 下面演示的是从左往右遍历，优先找右侧第一个更大的柱子，在弹出的过程中，去找栈里左侧比他大的柱子
        int len = height.size();
        int sum = 0;
        int tmpTop = 0;
        stack<int> s{};
        for (int i = 0; i < len; ++i)
        {
            while (!s.empty() && height[s.top()] < height[i])
            {
                // 当前柱子大于栈顶的柱子，需要对栈顶的柱子能集的雨水做一个记录
                if (s.size() > 1)
                {
                    // 要判断取出栈顶之后栈内还有没有元素
                    tmpTop = s.top();
                    s.pop();
                    sum += (min(height[s.top()], height[i]) - height[tmpTop]) * (i - s.top() - 1);
                }
                else
                {
                    // 取出栈顶元素之后，栈内没有元素，说明该栈顶柱子集不了水
                    s.pop();
                }
            }
            s.push(i); // 必须记录索引，这样才能知道水的宽度
        }
        return sum;
    }
};
int main()
{
    Solution so;
    vector<int> test{0, 1, 0, 2, 1, 0, 1, 3, 2, 1, 2, 1};
    cout << so.trap(test) << endl;
    return 0;
}