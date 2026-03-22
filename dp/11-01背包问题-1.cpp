#include "core.h"
#include "myclass.h"
#include "mytree.h"

using namespace std;

class Solution
{
public:
    int bag(int max_weight, vector<int> &obj_weight, vector<int> &obj_value)
    {
        vector<vector<int>> dp(obj_value.size(), vector<int>(max_weight + 1, 0));
        for (int i = 0; i < obj_value.size(); ++i)
        {
            // 外层是物品，内层是背包容量
            // 计算的核心思路是，遍历每一个物品，假设我一开始就知道有一个物品，
            // 然后通过遍历物品，那么我就可以新遍历的物品去优化我的背包所选择的物品有哪些
            // 所以一开始的思路就是用常识总结出如何遍历
            for (int j = 0; j < max_weight + 1; ++j)
            {
                // j是背包容量
                // 思路是要不要把之前加入背包的物品踢出去来存放当前物体
                // 判断的逻辑是，比较把踢出去之后的价值总量加上当前物体的价值与不加入当前物体的价值总量进行对比
                if (i == 0)
                {
                    if (j >= obj_weight[i])
                        dp[i][j] = obj_value[i];
                    continue;
                }
                if (j < obj_weight[i])
                {
                    dp[i][j] = dp[i - 1][j];
                    continue;
                }

                if (dp[i - 1][j - obj_weight[i]] + obj_value[i] > dp[i - 1][j])
                {
                    // 需要踢出去一点之前的物品
                    dp[i][j] = dp[i - 1][j - obj_weight[i]] + obj_value[i];
                }
                else
                {
                    // 不需要踢出去之前的物品,也就是不添加当前物体到背包
                    dp[i][j] = dp[i - 1][j];
                }
            }
        }
        return dp[obj_value.size() - 1][max_weight];

    }
};
int main()
{
    Solution so;
    TreeNode *root = nullptr;
    vector<int> test{1, 100, 1, 1, 1, 100, 1, 1, 100, 1};
    vector<vector<int>> test2{vector<int>{0, 0, 0, 0}, vector<int>{0, 0, 0, 1}, vector<int>{0, 0, 1, 0}, vector<int>{0, 0, 0, 0}};
    vector<int> obj_weight{1, 1, 1, 4};
    vector<int> obj_value{1, 2, 3, 4};
    int max_weight = 4;
    cout << so.bag(max_weight, obj_weight, obj_value) << endl;
}