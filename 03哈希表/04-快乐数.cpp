#include <bits/stdc++.h>
using namespace std;

class Solution
{
public:
    bool isHappy(int n)
    {
        // -- 思路
        // 通过简单几个输入案例进行测试，发现如果不是快乐数，那么其各位平方之和会出现在之前的计算结果里
        // 所以使用hashset
        // 通过简单测试，输入的快乐书最多是三位数，最大不超过999，因为999各位平方之后的结果才243
        unordered_set<int> set{n};
        auto getOutPut = [&set](int i) -> int
        {
            int sum = 0;
            while (i > 0)
            {
                int tmp = i % 10;
                sum += tmp * tmp;
                i /= 10;
            }
            return sum;
        };
        int output = n;
        while (output != 1)
        {
            output = getOutPut(output);
            if (output == 1)
                return true;
            if (set.find(output) != set.end())
            {
                // 输出值出现在之前的计算结果里
                return false;
            }
            else
                set.insert(output);
        }
        return true;
    }
};

int main()
{
    Solution s;
    cout << s.isHappy(7);
    return 0;
}