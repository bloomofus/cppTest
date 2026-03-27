#include "core.h"
#include "myclass.h"
#include "mytree.h"

using namespace std;

class Solution
{
public:
    int takeMaxValue(vector<int> &obj_weights, vector<int> &obj_values, int max_weight)
    {
        // dp[i]表示背包容量为I的时候能携带的最大价值
        // dp[i]初始化都是0
        // 由于是完全背包，所以遍历顺序是从前往后
        // 递推公式：dp[bag_weight] = dp[bag_weight - w] + v > dp[bag_weight] ? dp[bag_weight - w] + v:dp[bag_weight];
        vector<int> dp(max_weight + 1, 0);
        for (int i = 0; i < obj_weights.size(); ++i)
        {
            int w = obj_weights[i];
            int v = obj_values[i];
            for (int bag_weight = w; bag_weight <= max_weight; ++bag_weight)
            {
                dp[bag_weight] = dp[bag_weight - w] + v > dp[bag_weight] ? dp[bag_weight - w] + v : dp[bag_weight];
            }
        }
        return dp[max_weight];
    }
};

int main()
{
    Solution so;
    vector<int> obj_weights{1, 2, 3, 4};
    vector<int> obj_values{2, 4, 4, 5};

    cout << so.takeMaxValue(obj_weights, obj_values, 5) << endl;
}