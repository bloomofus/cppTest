#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    // -- 思路1（三重循环，最朴素的写法）:
    // 先排序，排序的好处是让元素有序，从而可以利用"和大于0就break"来提前剪枝，也能让去重变得简单
    // 排序后固定第一个数 a，再用 b、c 两个下标去找剩下两个数
    // 以 nums = [-1, 0, 1, 2, -1, -4] 为例，排序后变成 [-4, -1, -1, 0, 1, 2]
    // a=-4 时，b 从 -1 开始，c 从 b+1 开始一路往右扫，这一轮凑不出 0，全部 break 掉
    // a=-1 时，b 跳过第二个 -1（去重），b=0、c=1 时三数之和为 0，得到 [-1, 0, 1]
    // a 继续往右，a=0 已经大于 0，后面全是正数不可能凑成 0，直接 break
    // 去重策略：a 和 b 都要保证和上一个取值不同（用 lasta/lastb 记录），c 找到第一组合法值后直接 break
    // 缺点：c 每一轮 b 都要从 b+1 重新开始扫，存在大量重复计算
    vector<vector<int>> threeSum_1(vector<int>& nums) {
        if(nums.size()<3) return {};
        int lasta=-1,lastb=-1;
        vector<vector<int>> res{};
        std::sort(nums.begin(),nums.end());
        for(int a=0;a<nums.size()-2;++a)
        {
            // 当前 a 和上一轮的 a 相同，则这一轮 a 产生的所有组合都重复了，直接跳过
            if(lasta!=-1 && nums[a]==nums[a-1])
            {
                continue;
            }
            // a 已经大于 0，后面的 b、c 都比 a 大，三数之和只可能大于 0，直接结束
            if(nums[a]>0) break;
            lastb=-1; // 新一轮的循环必须重置lastb，否则会把上一轮 a 的 b 去重误用到这一轮
            for(int b=a+1;b<nums.size()-1;++b)
            {
                // b 去重：和这一轮上一个 b 相同就跳过（沿用上一轮思路）
                if(lastb!=-1&&nums[b]==nums[b-1]) continue;
                // a+b 已经大于 0，再加正的 c 只会更大，break
                if(nums[a]+nums[b]>0) break;
                for(int c=b+1;c<nums.size();++c)
                {
                    // a 和 b 负责去重，c 负责在右侧找能让三数之和为 0 的那个数
                    if(nums[a]+nums[b]+nums[c]<0) continue;
                    if(nums[a]+nums[b]+nums[c]==0)
                    {
                        res.push_back({nums[a],nums[b],nums[c]});
                        break; // 找到就 break，c 右侧再大的数三数之和只增不减
                    }
                    if(nums[a]+nums[b]+nums[c]>0) break;
                }
                lastb=b;
            }
            lasta=a;
        }
        return res;
    }

    // -- 思路2（对思路1的优化：把最内层循环改成双指针滑动）:
    // 思路1 最内层的 c 每轮 b 都要从 b+1 重新扫一遍，其实是浪费的
    // 因为固定 a 后，随着 b 右移，nums[a]+nums[b] 在增大，要凑成 0 所需的 c 应该在减小
    // 所以可以一开始让 c 指向数组末尾（最大的数），然后只让它往左移动
    // 以排序后的 [-4, -1, -1, 0, 1, 2] 为例：
    // a=-1 时，c 初始指向 2；b=-1，sum=-1+(-1)+2=0，得到 [-1,-1,2]，break 内层
    // b 移到 0，c 仍指向 2，sum=-1+0+2=1 > 0，于是 c 左移指向 1，sum=-1+0+1=0，得到 [-1,0,1]
    // 可以看到 c 只往左走，全程最多移动 n 次，没有重复扫描
    // 相比思路1 的优势：思路1 的 c 每轮从 b+1 重新扫，最坏是 O(n^3) 级别的循环次数；
    // 思路2 中 b 最多走 n 次，c 也最多走 n 次，整体稳定在 O(n^2)，常数更小、无冗余遍历
    // 进一步的剪枝：a 加其后最小两个数已 >0 则整体 break；a 加末尾最大两个数仍 <0 则跳过此 a
    // 命中三数之和为 0 后，顺手把左侧重复的 c 也跳掉，避免依赖边界情况产生重复组合
    vector<vector<int>> threeSum_2(vector<int>& nums) {
        if(nums.size()<3) return {};
        int lasta=-1,lastb=-1;
        vector<vector<int>> res{};
        std::sort(nums.begin(),nums.end());
        for(int a=0;a<nums.size()-2;++a)
        {
            if(lasta!=-1 && nums[a]==nums[a-1])
            {
                continue;
            }
            if(nums[a]>0) break;
            // 剪枝1：a 加其后最小的两个数（nums[a+1]+nums[a+2]）若已 >0，则这轮及之后所有 a 都无解，直接结束
            if(nums[a]+nums[a+1]+nums[a+2]>0) break;
            // 剪枝2：a 加末尾最大的两个数（nums[n-1]+nums[n-2]）若仍 <0，说明这个 a 太小凑不到 0，跳到下一个 a（不能 break，更大的 a 可能达标）
            if(nums[a]+nums[nums.size()-1]+nums[nums.size()-2]<0) continue;
            lastb=-1; // 新一轮的循环必须重置lastb
            int c=nums.size()-1; // c 从右边开始遍历，b 右移时 a+b 变大，所以 c 左移才能把和压回 0
            for(int b=a+1;b<c;++b)
            {
                if(lastb!=-1&&nums[b]==nums[b-1]) continue;
                if(nums[a]+nums[b]>0) break;
                // 内层不再是 for 全扫，而是用 while 让 c 只往左移动
                while(b<c)
                {
                    int sum_=nums[a]+nums[b]+nums[c];
                    if(sum_>0) --c;           // 和太大，说明 c 过大，c 左移让和变小
                    else if(sum_==0)
                    {
                        res.push_back({nums[a],nums[b],nums[c]});
                        // c 去重：命中后把左侧相同的 c 也跳掉，避免 b 变化时依赖边界产生重复组合
                        while(b<c && nums[c]==nums[c-1]) --c;
                        break;                 // 找到一组，b 右侧再找只会更大，退出内层
                    }
                    else break;                // sum_<0，说明 c 已经压到底了，这一轮 b 无解，直接换下一个 b
                }
                lastb=b;
            }
            lasta=a;
        }
        return res;
    }
};