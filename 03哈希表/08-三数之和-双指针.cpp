#include <bits/stdc++.h>
using namespace std;

class Solution
{
public:
    vector<vector<int>> threeSum(vector<int> &nums)
    {
        // -- 思路
        // 使用hashmap记录对应的组合值与索引值
        // 思路还是原来的思路，只不过在添加的时候，需要注意，索引是由小到大，着样就不会出现重复的组合
        // 按照上面的思路，输出的组合确实不会出现idx的重复，但是题目要求的是输出的集合不能重复
        // 删除重复的元素也是不行的，因为重复的元素也有可能组合为0
        // 可以对数组进行排序，这样能够减少很多判断，提前结束当前的循环，不管是数组的索引还是数字的大小都是由小到大
        // 假设有数组-3,-3,-3,-2,-2,-2，由于排序好了
        // 当我的i遍历到-3的时候，j在遍历的时候，在加入Map的时候，由于和Map[num]这个数组的最后一个重复了
        // 于是能够减少一部分重复的情况
        // 当i遍历到一个新的-3的时候，前面的-3已经把所有的组合情况加入map了，所以可以跳过
        // 当前两个数字的组合的和大于0的时候，就可以进行下一轮循环了
        // 因为我希望第三个数是大于0的，如果前两个组合都大于0，那么整体的组合不可能为0

        std::sort(nums.begin(),nums.end());
        if(nums[0]>0 || nums[nums.size()-1]<0) return {}; // 剪枝，去除全正全负的情况
        unordered_map < int,vector<pair<int, int>>> map{};
        for (int i = 0; i < nums.size();++i)
        {
            if(i>0 && nums[i]==nums[i-1])
            {
                // 该nums[i]为开始的组合之前已经被遍历过了
                continue;
            }
            for (int j = i+1; j < nums.size();++j)
            {
                if(j>i+1 && nums[j]==nums[j-1])
                {
                    // 这种情况已经被nums[j-1]遍历过了
                    continue;
                }
                if(nums[i]+nums[j]>0) continue; // 第三个数必定大于0
                if(map.find(nums[i]+nums[j])==map.end())
                {
                    map[nums[i] + nums[j]] = {{i, j}};
                }
                else
                    map[nums[i] + nums[j]].push_back({i, j});
            }
        }
        vector<vector<int>> res{};
        for (int i = 0; i < nums.size(); ++i)
        {
            // 遍历所有非0数，且要去重
            if(nums[i]<0 || // 第三个数必须大于等于0
                ( i+1<nums.size() && nums[i]==nums[i+1])) continue; // 直接跳到下一个相等的元素进行处理
            if(map.find(-nums[i])!=map.end())
            {
                for(auto idxPair:map[-nums[i]])
                {
                    if(i > idxPair.second)
                    {
                        res.push_back({nums[idxPair.first], nums[idxPair.second], nums[i]});
                    }
                }
            }
        }
        return res;
    }
};

class Solution2 {
public:
    vector<vector<int>> threeSum(vector<int>& nums) {
        // -- 思路
        // 上一个思路最终做出来了，但是效率很低，下面使用双指针的方法
        // 排序还是最首要的任务
        std::sort(nums.begin(),nums.end());
        if(nums[0]>0 || nums[nums.size()-1]<0) return {}; // 全正全负剪枝
        vector<vector<int>> res{};

        for(int i=0;i+2<nums.size();++i)
        {
            if((i>0 && nums[i]==nums[i-1]) || // 已经遍历过
                nums[i]>0 ) continue; // 第一个数大于0剪枝
            int r=nums.size()-1;
            int l=i+1;
            while(l<r)
            {
                // l从左往右，r就顺着l就从右往左
                int sum=nums[i]+nums[l]+nums[r];
                int target=0;
                if(sum>target)
                {
                    --r;
                }
                else if (sum<target)
                {
                    ++l;
                }
                else
                {
                    res.push_back({nums[i],nums[l],nums[r]});
                    //  跳过重复的数
                    while(l<r && nums[l]==nums[l+1]) ++l;
                    while(l<r && nums[r]==nums[r-1]) --r;
                    ++l;
                    --r;
                }

            }
        }
        return res;
    }
};

int main()
{
    Solution2 s;
    vector<int> test{2,-3,0,-2,-5,-5,-4,1,2,-2,2,0,2,-4,5,5,-10};
    s.threeSum(test);
    return 0;
}