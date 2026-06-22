#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    vector<vector<int>> fourSum(vector<int>& nums, int target) {
        // -- 思路
        // 可能和上一题一样，前面的两个数字自己写循环遍历，后边两个通过双指针去遍历
        std::sort(nums.begin(),nums.end());
        vector<vector<int>> res{};
        for(int i=0;i+3<nums.size();++i) 
        {
            // 当输入是{0}的时候nums.size()-3会发生无符号下溢，变成一个很大的正数，尽量避免
            if(i>0 && nums[i]==nums[i-1]) continue; // 之前遍历过了
            if(nums[i]>target && nums[i]>0) break;  // 剪枝
            for(int j=i+1;j+2<nums.size();++j)
            {
                if(j>i+1&& nums[j]==nums[j-1]) continue; // 之前遍历过了
                if(nums[i]+nums[j]>target && nums[i]+nums[j]>0) break; // 剪枝
                int l=j+1;
                int r=nums.size()-1;
                while(l<r)
                {
                    long long sum = (long long)nums[i] + nums[j] + nums[l] + nums[r]; // 避免溢出
                    if(sum>target) --r;
                    else if(sum <target) ++l;
                    else 
                    {
                        res.push_back({nums[i],nums[j],nums[l],nums[r]});
                        while(l<r && nums[l]==nums[l+1]) ++l;
                        while(l<r && nums[r]==nums[r-1]) --r;
                        ++l;
                        --r;
                    }
                }
            }
        }
        return res;
    }
};

int main()
{
    vector<int> test{0};
    Solution s;
    for(auto v:s.fourSum(test,0))
    {
        for(auto num:v)
            cout<<num<<" ";
        cout<<endl;
    }
    return 0;
}