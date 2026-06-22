#include <bits/stdc++.h>
using namespace std;

class Solution
{
public:
    vector<int> twoSum(vector<int> &nums, int target)
    {
        // -- 思路
        // 遍历数组中的每一个数，看看其另外一半是否在哈希表里
        unordered_map<int, int> map{};
        for (int i = 0; i < nums.size(); ++i)
        {
            int num = nums[i];
            if (map.find(target - num) == map.end())
            {
                map[num] = i;
            }
            else
                return {i, map[target - num]};
        }
        return {};
    }
};

int main()
{
    Solution s;
    vector<int> v{2, 7, 11, 15};
    s.twoSum(v, 9);
    return 0;
}