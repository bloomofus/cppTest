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
        // 这道题一个很明显的意图就是需要知道一个柱子其左边的最大值在哪和右边的最大值在哪
        // 因此是一个很明显的类似单调栈问题，但是如何转化是一个难点
        // 我一开始的思路是求每一个深V其能接收的雨水之和，但是这种方法有很多难点，首先就是，
        // 你要知道最深的一点在哪，然后向左右进行遍历，然后每个柱子还要记录其左边右边最大的柱子的位置
        // 不是第一个比他大的柱子
        // 转化一下，将一个深V转化为每一个小柱子的值之和
        // 因此只需要知道每一个柱子其左边的比他大最大值和右边的比他大最大值，如果两边缺少一个最大值，就说明该位置接不到水
        int len = height.size();
        vector<int> v1 = getRightMax(height);
        vector<int> v2 = getLeftMax(height);
        int sum = 0;
        for (int i = 0; i < len; ++i)
        {
            sum += getByRange(i, v1, v2, height);
        }
        // cout << res << endl;

        return sum;
    }

    int getByRange(int idx, vector<int> &v1, vector<int> &v2, vector<int> &height)
    {
        int l = v2[idx];
        int r = v1[idx];
        if (l == -1 || r == -1)
        {
            // 有一侧找不到比该柱子更高的，所以接不住水
            return 0;
        }
        else
        {
            return min(v1[idx], v2[idx]) - height[idx];
        }
    }

    vector<int> getRightMax(vector<int> &height)
    {
        // 包含该柱子的右侧的最高峰
        int len = height.size();
        vector<int> dp(len, -1);
        dp[len - 1] = height[len - 1];
        for (int i = len - 2; i >= 0; --i)
        {
            dp[i] = max(dp[i + 1], height[i]);
        }

#ifdef print
        cout << dp << endl;
#endif
        return dp;
    }

    vector<int> getLeftMax(vector<int> &height)
    {
        // 包含该柱子，其左侧的最高峰
        int len = height.size();
        vector<int> dp(len, -1);
        dp[0] = height[0];
        for (int i = 1; i < len; ++i)
        {
            dp[i] = max(dp[i - 1], height[i]);
        }

#ifdef print
        cout << dp << endl;
#endif
        return dp;
    }
};
int main()
{
    Solution so;
    vector<int> test{0, 1, 0, 2, 1, 0, 1, 3, 2, 1, 2, 1};
    cout << so.trap(test) << endl;
    return 0;
}