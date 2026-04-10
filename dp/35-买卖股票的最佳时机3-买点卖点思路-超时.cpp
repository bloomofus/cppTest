#include "core.h"
#include "utils/myclass.h"
#include "mystruct/mytree.h"

using namespace std;
using namespace mystruct;

class Solution
{
public:
    int maxProfit(vector<int> &prices)
    {
        // 核心思路：精准找到所有的买点和卖点，首先通过精简prices防止相等的股价对判断产生影响，方便操作
        //          然后第一天不可能是卖点，最后一天不可能是买点，这两种情况单独判断，找到所有的买卖点，直接求和作差即可
        vector<int> buyPoints{};
        vector<int> sellPoints{};
        auto mySubPrices = subPrices(prices);
        if (mySubPrices.size() < 2)
            return 0;
        for (int i = 0; i < mySubPrices.size(); ++i)
        {
            if (i == 0)
            {
                if (mySubPrices[1] > mySubPrices[0])
                    buyPoints.push_back(mySubPrices[i]);
                continue;
            }
            if (i == mySubPrices.size() - 1)
            {
                if (mySubPrices[i] > mySubPrices[i - 1])
                    sellPoints.push_back(mySubPrices[i]);
                continue;
            }
            if (mySubPrices[i - 1] > mySubPrices[i] && mySubPrices[i] < mySubPrices[i + 1])
                buyPoints.push_back(mySubPrices[i]);
            if (mySubPrices[i - 1] < mySubPrices[i] && mySubPrices[i] > mySubPrices[i + 1])
                sellPoints.push_back(mySubPrices[i]);
        }

        int sumProfit = 0;
        for (int i = 0; i < buyPoints.size(); ++i)
        {
            int sum1 = 0;
            for (int j = i; j < sellPoints.size(); ++j)
            {
                sum1 = sellPoints[j] - buyPoints[i];
                int sum2 = 0;
                for (int x = j + 1; x < buyPoints.size(); ++x)
                {
                    for (int y = x; y < sellPoints.size(); ++y)
                    {
                        sum2 = max(sellPoints[y] - buyPoints[x], sum2);
                    }
                }
                sumProfit = max(sumProfit, sum1 + sum2);
            }
        }
        return sumProfit;
    }

    vector<int> subPrices(vector<int> &prices)
    {
        if (prices.size() == 0)
            return {};
        vector<int> res{prices[0]};
        int lastNum = prices[0];
        for (int i = 1; i < prices.size(); ++i)
        {
            if (prices[i] == lastNum)
                continue;
            res.push_back(prices[i]);
            lastNum = prices[i];
        }
        return res;
    }
};

int main()
{
    Solution so;
    vector<int> test{3, 3, 5, 0, 0, 3, 1, 4};
    cout << so.maxProfit(test) << endl;
}