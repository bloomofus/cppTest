#include <bits/stdc++.h>
using namespace std;

class Solution
{
public:
    vector<int> intersection(vector<int> &nums1, vector<int> &nums2)
    {
        // -- 思路
        // 使用hashmap，为什么不使用hashset，因为Nums2里面可能有重复的数字，使用hashset检测麻烦一点
        unordered_map<int, bool> map{};
        vector<int> res{};
        for (auto num : nums1)
        {
            map[num] = false;
        }
        for (auto num : nums2)
        {
            if (map.find(num) != map.end() && map[num] == false)
            {
                res.push_back(num);
                map[num] = true;
            }
        }
        return res;
    }
};

int main()
{
    return 0;
}