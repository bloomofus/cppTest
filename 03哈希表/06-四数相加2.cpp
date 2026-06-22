#include <bits/stdc++.h>
using namespace std;

class Solution
{
public:
    int fourSumCount(vector<int> &nums1, vector<int> &nums2, vector<int> &nums3, vector<int> &nums4)
    {
        // -- 思路
        // 和两数之和类似，也是使用哈希表的问题
        // 但是有个注意点，需要先将数组1和数组2组合，然后将数组3和数组4组合，这样复杂度是o(2)
        // 但是如果你先将数组1和数组2组合，其组合的结果再和数组3组合，这样复杂度却是o(3)
        unordered_map<int, int> map{}; // map的值是当前组合的数字的可能性有几个
        for (int i = 0; i < nums1.size(); ++i)
        {
            for (int j = 0; j < nums2.size(); ++j)
            {
                if (map.find(nums1[i] + nums2[j]) == map.end())
                {
                    map[nums1[i] + nums2[j]] = 1;
                }
                else
                    map[nums1[i] + nums2[j]]++;
            }
        }
        int num = 0;
        for (int i = 0; i < nums3.size(); ++i)
        {
            for (int j = 0; j < nums4.size(); ++j)
            {
                if (map.find(-nums3[i] - nums4[j]) != map.end())
                    num += map[-nums3[i] - nums4[j]];
            }
        }
        return num;
    }
};

int main()
{
    vector<int> v1 = {-1, -1};
    vector<int> v2 = {-1, 1};
    vector<int> v3 = {-1, 1};
    vector<int> v4 = {1, -1};
    Solution s;
    s.fourSumCount(v1, v2, v3, v4);
    return 0;
}