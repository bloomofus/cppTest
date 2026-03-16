#include "core.h"
#include "myclass.h"
#include "mytree.h"

using namespace std;

void printMatrixStyle(const std::vector<std::vector<int>> &vec);
vector<vector<int>> sortIntervals(vector<vector<int>> &intervals);

class Solution
{
public:
    int climbStairs(int n)
    {
        // dp数组压缩
        if (n <= 3)
            return n;
        int dp[2]{1, 2};
        bool left{false};
        int now = 3;
        while (now != n + 1)
        {
            dp[left] = dp[0] + dp[1];
            left = !left;
            ++now;
        }
        return dp[!left];
    }
};

int main()
{
    Solution so;
    TreeNode *root = nullptr;
    cout << so.climbStairs(3) << endl;
    // std::cout<< so.reconstructQueue(tmp) << std::endl;
    // printMatrixStyle(input_data);
}