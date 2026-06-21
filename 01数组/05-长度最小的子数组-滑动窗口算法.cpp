#include <bits/stdc++.h>
using namespace std;

class Solution
{
public:
    int minSubArrayLen(int target, vector<int> &nums)
    {
        // -- 思路
        // 通过l以及r实现滑动窗口
        // 每次使用r进行遍历，发现满足需求的时候，再从l开始遍历，直到不满足需求，然后退出循环
        // 于是得到一个满足需求的一个窗口长度r-l+1
        // 但是r在对整个nums遍历的时候，会不断出现新的窗口组合能够满足需求
        // 所以就需要比较每次窗口组合中最小的留下来；使用min函数进行更新
        int l = 0;
        int sum = 0;
        int minLenth = INT_MAX;
        for (int r = 0; r < nums.size(); ++r)
        {
            sum += nums[r];
            if (sum >= target)
            {
                for (int i = l; i <= r; ++i)
                {
                    if (sum - nums[i] >= target)
                    {
                        sum = sum - nums[i];
                        l++;
                    }
                    else
                        break;
                }
                minLenth = min(minLenth, r - l + 1);
            }
        }
        return sum >= target
                   ? minLenth
                   : 0;
    }
};

int main()
{
    Solution so;
    vector<int> test{1, 2, 3, 4, 5};
    auto print_arr = [&](vector<int> &v) -> void
    {
        for (auto num : v)
            cout << num << " ";
    };
    auto res = so.minSubArrayLen(15, test); // 1
    // print_arr(res);
    cout << res;

    return 0;
}