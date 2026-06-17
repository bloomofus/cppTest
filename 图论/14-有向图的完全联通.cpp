#include <bits/stdc++.h>
using namespace std;

int main()
{
    // -- 思路
    // 主要看看这个邻接链表的构建方式
    // 之前节点为字符串，我使用的是map+listNode，map[str]=listNode*
    // 由于这里节点是数字，那么就可以使用vector+vector来构建
    // 通过一个简单的bfs/dfs对各节点进行遍历即可实现，再加上一个closed数组记录遍历状态即可
    // 当队列不为空，遍历当前节点，将当前节点加入closed数组，再将当前节点的下游节点加入closed数组

    // -- 输入数据 && 构建邻接链表
    int n, m; // n是节点数，m是行数
    cin >> n >> m;
    vector<vector<int>> g(n + 1, vector<int>{});
    for (int i = 0; i < m; ++i)
    {
        int node, nextNode;
        cin >> node >> nextNode;
        g[node].push_back(nextNode);
    }

    // -- bfs
    auto bfs = [&](int node) -> unordered_set<int>
    {
        // 输入一个节点，输出对应的可达节点
        unordered_set<int> closed{node}; // 里面的节点就是全部可达节点
        deque<int> processV{node};
        while (!processV.empty())
        {
            int curNodeNum = processV.size();
            while (curNodeNum--)
            {
                for (auto nextNode_ : g[processV.front()])
                {
                    // 把当前节点的其余可达节点加入处理队列
                    if (closed.find(nextNode_) == closed.end())
                    {
                        // 没找到，说明nextNode_没有被访问
                        closed.insert(nextNode_);
                        processV.push_back(nextNode_);
                    }
                }
                processV.pop_front();
            }
        }
        return closed;
    };

    auto bfs2 = [&](int node) -> unordered_set<int>
    {
        // 输入一个节点，输出对应的可达节点
        unordered_set<int> closed{node}; // 里面的节点就是全部可达节点
        deque<int> processV{node};
        while (!processV.empty())
        {
            int top = processV.front();
            processV.pop_front();
            for (auto nextNode_ : g[top])
            {
                // 把当前节点的其余可达节点加入处理队列
                if (closed.find(nextNode_) == closed.end())
                {
                    // 没找到，说明nextNode_没有被访问
                    closed.insert(nextNode_);
                    processV.push_back(nextNode_);
                }
            }
        }
        return closed;
    };

    auto dfs = [&](int node) -> unordered_set<int>
    {
        unordered_set<int> closed{node}; // 里面的节点就是全部可达节点
        deque<int> processV{node};
        while (!processV.empty())
        {
            int top = processV.back();
            processV.pop_back();
            for (auto nextNode_ : g[top])
            {
                // 把当前节点的其余可达节点加入处理队列
                if (closed.find(nextNode_) == closed.end())
                {
                    // 没找到，说明nextNode_没有被访问
                    closed.insert(nextNode_);
                    processV.push_back(nextNode_);
                }
            }
        }
        return closed;
    };

    // -- 主循环
    unordered_set<int> reachNodes = bfs(1);
    for (int i = 1; i <= n; ++i)
    {
        if (reachNodes.find(i) == reachNodes.end())
        {
            cout << -1;
            return 0;
        }
    }
    cout << 1;
    return 0;
}