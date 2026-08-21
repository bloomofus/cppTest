#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    vector<int> topKFrequent(vector<int>& nums, int k) {
        // -- 思路:
        // 1. 使用哈希表统计每个元素的出现频率
        // 2. 维护一个大小为k的小顶堆，堆中存储<元素, 频率>对
        // 3. 遍历哈希表，频率大于堆顶的入堆并弹出堆顶，保证堆内始终是前k个高频元素
        unordered_map<int, int> map;
        for (int num : nums) map[num]++;

        auto cmp = [](const pair<int, int>& a, const pair<int, int>& b) {
            return a.second > b.second;
        };
        priority_queue<pair<int, int>, vector<pair<int, int>>, decltype(cmp)> pq(cmp);

        for (auto& [num, count] : map) {
            pq.push({num, count});
            if (pq.size() > k) pq.pop();
        }

        vector<int> res(k);
        for (int i = k - 1; i >= 0; --i) {
            res[i] = pq.top().first;
            pq.pop();
        }
        return res;
    }
};
