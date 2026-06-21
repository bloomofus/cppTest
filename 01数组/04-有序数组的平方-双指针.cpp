#include <bits/stdc++.h>
using namespace std;

class Solution
{
public:
    vector<int> sortedSquares(vector<int> &nums)
    {
        // 先将负数变成正数，再排序，再进行平方操作
        // 平方追加的时候使用一个变量记录平方数组的最后一个数，就能够防止重复加入
        for (int i = 0; i < nums.size(); ++i)
            nums[i] = (nums[i] < 0 ? -nums[i] : nums[i]);
        std::sort(nums.begin(), nums.end());
        vector<int> res{};
        int squareLast = -1;
        for (int i = 0; i < nums.size(); ++i)
        {
            int squareNum = nums[i] * nums[i];
            if (squareNum != squareLast)
                res.push_back(squareNum);
        }
        return res;
    }
};

class Solution2
{
public:
    vector<int> sortedSquares(vector<int> &nums)
    {
        // 找到中间的元素，然后向两边拓展
        // 题目既然给了数组是有序的，如果是第一种思路就没有使用到这个条件
        // 如何找到中间的元素？查看数组绝对值的升降，如果一开始数组绝对值就是上升
        //      那么第一个值就是最小值，如果先降后升，那么拐点就是最小值
        //      如果一直下降，那么最后一个数值是最小值
        //      所以就是说，最小值是最后一个下降的点或者第一个上升的点前一个点
        //      但是？这个过程的需要判断的东西很多，很容易出错
        //      又联想到，数组是有负转正，那么比较最后一个负数和第一个正数即可，
        //      这样更容易
        auto findMinIdx = [&]() -> int
        {
            int negitive = -1; // 初始化为-1
            int positive = -1;
            for (int i = 0; i < nums.size(); ++i)
            {
                if (nums[i] < 0)
                    negitive = i; // 出现负数就更新负数索引
                else if (nums[i] == 0)
                    return i; // 出现0直接返回对应的idx
                else
                {
                    // 出现了正数，说明没有0，就需要比较一下和负数的大小
                    return negitive == -1 ? i : (-nums[negitive] > nums[i] ? i : negitive);
                }
            }
            return negitive;
        };
        auto findMinIdx2 = [&]() -> int
        {
            // 还是这种遍历简单
            int minIdx = 0;
            for (int i = 1; i < nums.size(); ++i)
            {
                if (abs(nums[i]) < abs(nums[minIdx]))
                {
                    minIdx = i;
                }
            }
            return minIdx;
        };
        int minIdx = findMinIdx2();
        vector<int> res{nums[minIdx] * nums[minIdx]};
        int l = minIdx;
        int r = minIdx;
        int L = l - 1;
        int R = r + 1;
        while ((L >= 0 && L <= nums.size() - 1) || (R >= 0 && R <= nums.size() - 1))
        {
            int leftNum = INT_MAX;
            int rightNum = INT_MAX;
            if (L >= 0 && L <= nums.size() - 1)
                leftNum = nums[L] * nums[L];
            if (R >= 0 && R <= nums.size() - 1)
                rightNum = nums[R] * nums[R];
            if (leftNum < rightNum)
            {
                res.push_back(leftNum);
                L--;
            }
            else
            {
                res.push_back(rightNum);
                R++;
            }
        }
        return res;
    }
};

class Solution3
{
public:
    vector<int> sortedSquares(vector<int> &nums)
    {
        // 之前是由中间节点向两边扩散，但是逆过来想，从两边到中间更容易
        // 虽然一开始res是反着的，但是遍历一遍即可
        vector<int> res_less{};
        int l = 0;
        int r = nums.size() - 1;
        while (l <= r)
        {
            int lval = nums[l] * nums[l];
            int rval = nums[r] * nums[r];
            if (lval > rval)
            {
                res_less.push_back(lval);
                l++;
            }
            else
            {
                res_less.push_back(rval);
                r--;
            }
        }
        auto reverse = [&](const vector<int> &v) -> vector<int>
        {
            vector<int> res;
            res.reserve(v.size());
            for (int i = 0; i < v.size(); ++i)
            {
                res.push_back(v[v.size() - i - 1]);
            }
            return res;
        };

        auto reverse2 = [&](vector<int> &v) -> vector<int>
        {
            // 上面的算法还需要额外占用内存
            // 可以通过双指针进行原位翻转
            int l = 0;
            int r = v.size() - 1;
            while (l < r)
            {
                v[l] ^= v[r];
                v[r] ^= v[l];
                v[l] ^= v[r];
                l++;
                r--;
            }
            return v;
        };

        return reverse2(res_less);
    }
};

class Solution4
{
public:
    vector<int> sortedSquares(vector<int> &nums)
    {
        // 之前是由中间节点向两边扩散，但是逆过来想，从两边到中间更容易
        // 在比较双边大小的时候，往res里面添加可以直接添加在末尾，这样省去反转的消耗
        // 只需要使用一个idx记录当前添加位置即可
        int curIdx = nums.size() - 1;
        vector<int> res(nums.size(), 0);
        int l = 0;
        int r = nums.size() - 1;
        while (l <= r)
        {
            int lval = nums[l] * nums[l];
            int rval = nums[r] * nums[r];
            if (lval > rval)
            {
                res[curIdx--] = lval;
                l++;
            }
            else
            {
                res[curIdx--] = rval;
                r--;
            }
        }
        return res;
    }
};

int main()
{
    // -- 思路
    Solution4 so;
    vector<int> test{-7, -3, 2, 3, 11};
    auto print_arr = [&](vector<int> &v) -> void
    {
        for (auto num : v)
            cout << num << " ";
    };
    auto res = so.sortedSquares(test);
    print_arr(res);

    return 0;
}