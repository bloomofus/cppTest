#include "core.h"
#include "myclass.h"
#include "mytree.h"

using namespace std;

class Solution
{
public:
    int bag(int max_weight, vector<int> &obj_weight, vector<int> &obj_value)
    {
        // 这个与上一个算法不同之处在于上一个算法使用的是二维数组，这个使用的是一维数组
        vector<int> dp(max_weight + 1, 0);
        for (int i = 0; i < obj_value.size(); ++i)
        {
            // 外层是物品，内层是背包容量
            // 计算的核心思路是，遍历每一个物品，假设我一开始就知道有一个物品，
            // 然后通过遍历物品，那么我就可以新遍历的物品去优化我的背包所选择的物品有哪些
            // 所以一开始的思路就是用常识总结出如何遍历
            for (int j = max_weight; j >= obj_weight[i]; --j)
            {
                // 一维数组和二维数组的主要区别在于，
                // 其背包重量的遍历顺序是从大到小，而二维数组的遍历顺序是从小到大
                // 一维数组这样遍历的原因是，背包大重量需要上一轮循环背包小重量的值
                // 如果背包从小到大遍历，那么这个值就会被修改
                if (dp[j - obj_weight[i]] + obj_value[i] > dp[j])
                {
                    dp[j] = dp[j - obj_weight[i]] + obj_value[i];
                }
            }
        }
        return dp[max_weight];
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