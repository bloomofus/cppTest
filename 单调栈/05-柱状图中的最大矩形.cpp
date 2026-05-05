#include "core.h"
#include "utils/myclass.h"
#include "mystruct/mytree.h"

using namespace std;
using namespace mystruct;

#define print

class Solution
{
public:
    int largestRectangleArea(vector<int> &heights)
    {
        // 一个比较明显的思路就是，根据最后组成的矩形的高度进行遍历
        // 然后找出能满足对应高度的所有柱子，这里可能有好几个组合
        // 然后就找出这几个组合里的最大值作为该高度的矩形最大大小
        // 但是上面的思路很简单，算法效率就低了，因为我要去遍历各个组合
        // 就需要我事先找到其高度或者实时去遍历
        // 通过一个简单的思路变化就很好解决这个问题
        // 我不去遍历所有的可能高度
        // 而是去遍历所有的柱子，每个柱子都有其对应的组合，我记录这个组合组成的矩形的最大值即可
        // 这种情况下就需要记录该柱子左侧第一个比它小的柱子的索引，以及右侧的
        // 注意，如果找不到，在对应v里面会使用-1代替，需要额外判断一点东西
        int maxSize = 0;
        int len = heights.size();
        vector<int> v1(len, -1); // 左侧更小的
        vector<int> v2(len, -1); // 右侧
        stack<int> s1{};
        stack<int> s2{};
        for (int i = 0; i < len; ++i)
        {
            while (!s2.empty() && heights[s2.top()] > heights[i])
            {
                v2[s2.top()] = i;
                s2.pop();
            }
            s2.push(i);
        }
        for (int i = len - 1; i >= 0; --i)
        {
            while (!s1.empty() && heights[s1.top()] > heights[i])
            {
                v1[s1.top()] = i;
                s1.pop();
            }
            s1.push(i);
        }
        cout << v1;
        cout << v2;
        for (int i = 0; i < len; ++i)
        {
            v1[i] = (v1[i] == -1) ? 0 : (v1[i] + 1);         // v1[i]现在表示对应组合起始节点
            v2[i] = (v2[i] == -1) ? (len - 1) : (v2[i] - 1); // v2[i]现在表示对应组合结束节点
            maxSize = max(maxSize, (v2[i] - v1[i] + 1) * heights[i]);
        }
        return maxSize;
    }
};
int main()
{
    Solution so;
    vector<int> test{2, 1, 5, 6, 2, 3};
    cout << so.largestRectangleArea(test) << endl;
    return 0;
}