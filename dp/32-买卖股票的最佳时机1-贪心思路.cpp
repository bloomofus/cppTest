#include "core.h"
#include "utils/myclass.h"
#include "mystruct/mytree.h"

using namespace std;
using namespace mystruct;

class Solution {
    public:
    int maxProfit(vector<int>& prices) {
        //贪心思路的核心就是尽力寻找低价股的位置，并且实时更新最大利润
        //贪心这里没有记录右侧的最大值，是因为如果记录右侧最大值之后股价又创新低
        // 但是后续股价回升得到的利润没有之前的买卖区间得到的收益更高
        //只有记录最大利润才能解决这个问题
        int low = INT_MAX;
        int result = 0;
        for (int i = 0; i < prices.size(); i++) {
            low = min(low, prices[i]);  // 取最左最⼩价格
            result = max(result, prices[i] - low); // 直接取最⼤区间利润
        }
        return result;
    }
};

int main()
{
    Solution so;
    vector<int> test{3, 5, 0, 0, 1,1};
    cout << so.maxProfit(test) << endl;
}