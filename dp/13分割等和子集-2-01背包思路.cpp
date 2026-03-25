#include "core.h"
#include "myclass.h"
#include "mytree.h"

using namespace std;

class Solution
{
public:
    bool canPartition(vector<int> &nums)
    {
        //相当于从Nums找出一些数使其之和等于target；
        //这个过程就相当于拿东西放到背包里面，因此可以考虑01背包的思路
        //背包的容量就是target，目标就是将Nums放入背包
        //那么质量和价值怎么确定，确定方法就是质量和价值就等于num，
        //因此背包放了多少重量的物体，那么其价值也就是多少
        //最后比较dp[target]是否和target相等即可
        //具体细节就是常规的01背包问题
        int sum = 0;
        for (auto num : nums)
            sum += num;
        if (sum % 2 == 0)
        {
            int target = sum / 2;
            vector<int> dp(target + 1, 0);
            for (auto num : nums)
            {
                for (int j = target; j >= num; --j)
                {
                    if (dp[j - num] + num > dp[j])
                        dp[j] = dp[j - num] + num;
                }
                if (dp[target] == target)
                    return true;
            }
        }
        return false;
    }
};
int main()
{
    Solution so;
    vector<int> test{1, 5, 11, 5};
    cout << so.canPartition(test) << endl;
}