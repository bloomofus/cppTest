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
        // 还有一个思路就是水面的高度，一个很显然的道理就是
        // 最高的水位一定是位于中间部分，两边的水位都是比中间低一点的
        // 假如我从左往右遍历，我记录最高柱子的高度，假如右侧始终有柱子比最高柱子更高
        //     那么，左侧的最高水位就是最高柱子高度
        // 如果从右往左遍历也是一个道理
        // 对于每一个柱子，其左侧最高水位和右侧最高水位的较低值就是该柱子的水位
        // 问题在于如何去更新双指针，
        // 其实这个思路和dp思路也很类似，dp思路先求出每个柱子两侧的最值，也就是该柱子的最高水位
        // 但是这个双指针思路却是一边遍历，遍历的同时记录两侧的柱子最值，
        // 而且是从两侧同时遍历，因为只有两侧的最值是确定的，其余中间的是不确定的，
        // 而且根据最两侧的柱子最值，判断是左侧的水位确定还是右侧的水位能确定
        // 在能确定水位的一侧往前走，继续遍历，然后去更新两侧柱子最值
        // 这样既有dp寻找最值的效率，又减少了存储空间
        int len = height.size();
        int sum = 0;
        int l = 0;
        int r = len - 1;
        int l_max = height[l];
        int r_max = height[r];
        while (l < r)
        {
            l_max = max(l_max, height[l]);
            r_max = max(r_max, height[r]);
            if (l_max >= r_max)
            {
                // 确定r柱子的水位是r_max，但是l柱子的水位还不确定
                sum += r_max - height[r];
                --r;
            }
            else
            {
                // 确定l柱子的水位是l_max，但是r柱子的水位还不确定
                sum += l_max - height[l];
                ++l;
            }
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