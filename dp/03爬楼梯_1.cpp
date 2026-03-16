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
        if (n <= 3)
            return n;
        int dp[n + 1];
        dp[1] = 1;
        dp[2] = 2;
        int now = 3;
        while (now != n + 1)
        {
            dp[now] = dp[now - 1] + dp[now - 2];
            ++now;
        }
        return dp[n];
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