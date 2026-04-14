#include "core.h"
#include "utils/myclass.h"
#include "mystruct/mytree.h"

using namespace std;
using namespace mystruct;

class Solution
{
public:
    int findLengthOfLCIS(vector<int> &nums)
    {
        int len = nums.size();
        int maxLen = 1;
        vector<int> dp(len, 1);
        for (int i = 1; i < len; ++i)
        {
            if (nums[i] > nums[i - 1])
                dp[i] = 1 + dp[i - 1];
            maxLen = max(maxLen, dp[i]);
        }
        return maxLen;
    }
};
int main()
{
    Solution so;
    vector<int> test{1, 3, 5, 4, 7};
    cout << so.findLengthOfLCIS(test) << endl;
}