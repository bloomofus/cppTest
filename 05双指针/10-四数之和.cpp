#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    vector<vector<int>> fourSum(vector<int>& nums, int target) {
        // -- 思路:
        // 先排序，然后固定前三个数 a/b/c，用双指针找第四个数 d
        // 排序后数组有序，便于去重和剪枝
        // 去重方式：用 lasta/lastb/lastc 记录上一轮的索引，如果值相同就跳过
        // 剪枝1：如果当前最小的四个数之和已经大于 target，后面不可能有解，直接 continue
        // 剪枝2：如果当前 a 加上最大的三个数之和仍小于 target，这个 a 太小，跳过
        // 找 d 时利用有序性：sum > target 说明 d 太大，--d；sum < target 说明 c 太小，break 进入下一轮 c
        if(nums.size()<4) return {};
        std::sort(nums.begin(),nums.end());
        int lasta=-1,lastb=-1,lastc=-1;
        vector<vector<int>> res{};
        for(int a=0;a<nums.size()-3;++a)
        {
            if(lasta!=-1&&nums[lasta]==nums[a]) continue;
            if((long long)nums[a]+nums[a+1]+nums[a+2]+nums[a+3]>target) continue;
            if((long long)nums[a]+nums[nums.size()-3]+nums[nums.size()-2]+nums[nums.size()-1]<target) continue;
            lastb=-1;
            for(int b=a+1;b<nums.size()-2;++b)
            {
                if(lastb!=-1&&nums[lastb]==nums[b]) continue;
                int d=nums.size()-1;
                lastc=-1;
                for(int c=b+1;c<d;++c)
                {
                    if(lastc!=-1&&nums[c]==nums[lastc]) continue;
                    // 通过循环遍历查找对应的d
                    while(c<d)
                    {
                        long long sum_=(long long)nums[a]+nums[b]+nums[c]+nums[d];
                        if(sum_>target) --d;
                        else if(sum_==target)
                        {
                            res.push_back({nums[a],nums[b],nums[c],nums[d]});
                            while(c<d && nums[d-1]==nums[d]) --d;
                            break;
                        }
                        else break; // 没有合适的d直接进行下一轮
                    }
                    lastc=c;
                }
                lastb=b;
            }
            lasta=a;
        }
        return res;
    }
};