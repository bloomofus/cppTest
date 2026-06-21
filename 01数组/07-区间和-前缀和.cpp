#include <bits/stdc++.h>
using namespace std;

class Solution
{
public:
    void areaSum()
    {
        // -- 思路
        // 题目要我们求区间start->end的和
        // 肯定能依次累加
        // 所以可以通过一个数组记录前n个元素的求和
        // 所以区间和就变成arr[end]-arr[start-1]，时间复杂度就是o(n)

        // -- 输入
        int n, a, b;
        cin >> n;
        vector<int> arr(n);
        for (int i = 0; i < n; ++i)
            cin >> arr[i];
        vector<pair<int, int>> quests{};
        while (cin >> a >> b)
            quests.push_back({a, b});
        // -- 核心算法
        vector<int> forntSum(n, 0); // forntSum[i]表示输入arr里面前i+1个元素的求和
        for (int i = 0; i < n; ++i)
        {
            if (i != 0)
                forntSum[i] = forntSum[i - 1] + arr[i];
            else
            {
                // 需要初始化
                forntSum[0] = arr[0];
            }
        }
        for (int i = 0; i < quests.size(); ++i)
        {
            int start = quests[i].first;
            int end = quests[i].second;
            if (start == 0)
                cout << forntSum[end];
            else
                cout << forntSum[end] - forntSum[start - 1];
            cout << (i == quests.size() - 1 ? "" : "\n");
        }
    }
};

int main()
{
    Solution so;
    so.areaSum();
    return 0;
}