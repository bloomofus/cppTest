#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    int removeElement(vector<int>& nums, int val) {
        // -- 思路
        // fast指针是遍历数组的排头兵，slow指针是修改当前位的指针
        // 题目需要知道修改后的长度，就是slow的位置索引
        int fast=0;
        int slow=0;
        while(fast<nums.size())
        {
            if(nums[fast]==val)
            {
                // 找到目标数字，fast向前移动，slow不变
                // 等到下一步，fast所在位置不是val的时候，slow所在的位置就需要变成val
                ++fast;
            }
            else 
            {
                // 要看fast和slow位置是不是一个位置
                // 如果是同一个位置，那么他们就需要一起向前
                if(fast==slow) 
                {
                    ++fast;
                    ++slow;
                }
                else
                {
                    // 否则，slow位置需要更新fast位置的值
                    nums[slow]=nums[fast];
                    ++fast;
                    ++slow;
                }
            }
        }
        return slow;
    }
};

