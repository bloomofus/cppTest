#include <bits/stdc++.h>
using namespace std;

class Solution
{
public:
    int removeElement(vector<int> &nums, int val)
    {
        int fast = 0;
        int slow = 0;
        int k = 0;
        while (fast != nums.size())
        {
            if (nums[fast] != val)
            {
                // 快指针去遍历，慢指针去更新
                k++;
                nums[slow] = nums[fast];
                fast++;
                slow++;
            }
            else
            {
                fast++;
            }
        }
        return k;
    }
};

int main()
{
    // -- 思路

    return 0;
}