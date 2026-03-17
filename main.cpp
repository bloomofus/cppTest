#include "core.h"
#include "myclass.h"
#include "mytree.h"

using namespace std;

class Solution
{
public:
    int bag(int max_weight,vector<int>& obj_weight,vector<int>& obj_value)
    {
        vector<int> dp(obj_value.size() + 1, 0);
        vector<vector<int>>
            take(max_weight + 1, vector<int>(obj_value.size(), 0));
        for (int i = 1; i < obj_value.size();++i)
        {
            //先看有没有刚好时候背包的尺寸的物品，再看更小的物品和dp[n-i]的组合；
            for (int j = 0; j < obj_value.size();++j)
            {
                if()
            }
        }

            ;
        return 0;
    }
};
int main()
{
    Solution so;
    TreeNode *root = nullptr;
    vector<int> test{1, 100, 1, 1, 1, 100, 1, 1, 100, 1};
    vector<vector<int>> test2{vector<int>{0, 0, 0,0},vector<int>{0,0,0,1},vector<int>{0,0,1,0},vector<int>{0,0,0,0}};
    vector<int> obj_weight{1, 1, 1, 4};
    vector<int> obj_value{1, 2, 3, 4};
    int max_weight = 4;
    cout << so.bag(max_weight,obj_weight,obj_value) << endl;
}