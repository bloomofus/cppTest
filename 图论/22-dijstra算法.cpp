#include <bits/stdc++.h>
using namespace std;

int main()
{
    // -- 思路
    // dijstra算法里面的节点有三种状态，首先就是完全不确定状态，那么从开始节点到该节点距离就是int_max
    // 其次就是半确定状态，确定了目前的最短距离，但是还是有可能有更短的路径，比如从开始节点，第一次向其下游节点开始探索
    // 那么开始节点的下游节点都变成这种半确定状态
    // 最后就是完全确定状态，比如开始节点就是完全确定状态，其最短路径就是0，不可能有比这还短的
    // 如果其他节点也想变成最短路径状态，那么其全部上游节点都必须是完全确定状态，才能将这个节点变成完全确定状态
    //
    // dijstra的处理可以理解为信息的处理，开始节点有最短路径信息，那么我遍历该节点之后，就能把该信息传递给起始节点的下游节点
    // 那么再次遍历起始节点就没什么作用了，所以要将其加入closed数组
    // 而之前的下游节点有了新的最短路径消息（更新了），那么遍历这些下游节点，再将信息传递下去
    // 传递成功的标志就是下游节点的dist更新了，如果一个节点处于当前的处理队列，
    // 但是在遍历当前处理队列的时候，其最短路径也更新了，那么也要将其加入新的处理队列
    // 在遍历处理队列里的节点，每次遍历之后，就将其加入closed数组，但是如果后来其又加入新的处理队列之后
    // 也需要将其拉出closed数组
    // 所以综合就是，处理队列处理当前节点，当前节点进入closed数组
    // 有下游节点的dist信息更新了，其closed对应值设为false
    // 不过好像这里的closed没啥用，closed只是表示当前的节点暂时没啥信息可用了，不初始化也没事
    // 更正：如果是使用队列处理待处理节点，那么一般是不需要closed数组的，如果是使用dist数组寻找待处理节点，就需要closed数组
    //
    // 根据代码可以看出，如果每次不是选取最短的不在closed里的节点，而是处理当前轮次的所有节点，update就可以生效
    // 如果选取最短距离的节点来处理，就无法使用update来提前结束了

    // -- 输入数据
    int n, m;
    cin >> n >> m;
    vector<vector<pair<int, int>>> g(n + 1); // 邻接表：g[u] = {(v, w), ...} 表示从 u 到 v 权重为 w

    for (int i = 0; i < m; ++i)
    {
        int a, b, c;
        cin >> a >> b >> c;
        g[a].push_back({b, c});
        // 如果是无向图，添加反向边（权重也是 c，不是 -c！）
        // g[b].push_back({a, c});
    }

    // -- Dijkstra 算法
    auto dijstra_1 = [&]() -> void
    {
        // 从信息的角度实现dijstra算法,使用dist数组查找待处理节点，需要closed数组
        vector<int> dist(n + 1, INT_MAX);
        dist[1] = 0;
        vector<bool> closed(n + 1, false);
        while (1)
        {
            // 寻找所有有可用信息的节点
            vector<int> processV{}; // 处理队列
            for (int i = 1; i <= n; ++i)
            {
                if (dist[i] != INT_MAX && closed[i] == false)
                {
                    // 当前节点没有加入closed数组，并且距离不是int_max，说明该节点有可用的信息，需要加入处理队列
                    processV.push_back(i);
                }
            }
            if (processV.size() == 0)
            {
                // 说明没有节点能提供更有用的信息了，需要退出循环
                break;
            }

            // 遍历所有有信息的节点
            bool update = false;
            for (auto curNode : processV)
            {
                // 用完curNode的信息就需要将其加入closed数组
                closed[curNode] = true;
                for (auto [v, w] : g[curNode])
                {
                    // 遍历curNode所有的边信息
                    if (dist[curNode] + w < dist[v])
                    {
                        // 出现更新行为，被更新的节点带有有用信息，其closed数组需要设置为false
                        dist[v] = dist[curNode] + w;
                        closed[v] = false;
                        update = true;
                    }
                }
            }
            if (!update)
                break; // 提前结束
        }
        cout << (dist[n] == INT_MAX ? -1 : dist[n]);
    };
    auto dijstra_2 = [&]() -> void
    {
        // 从信息的角度实现dijstra算法,使用队列处理，不需要closed数组
        vector<int> dist(n + 1, INT_MAX);
        dist[1] = 0;
        // vector<bool> closed(n + 1, false);
        // closed[1] = true;
        queue<int> processV{};
        processV.push(1);
        while (!processV.empty())
        {
            int curSize = processV.size();
            bool update = false;
            while (curSize--)
            {
                int curNode = processV.front();
                processV.pop();
                // closed[curNode] = true;

                for (auto edge : g[curNode])
                {
                    int v = edge.first;
                    int w = edge.second;
                    if (dist[curNode] + w < dist[v])
                    {
                        // 发生更新行为
                        dist[v] = dist[curNode] + w;
                        // closed[v] = false;
                        processV.push(v);
                        update = true;
                    }
                }
            }
            if (!update)
                break;
        }
        cout << (dist[n] == INT_MAX ? -1 : dist[n]);
    };

    auto dijstra_3 = [&]() -> void
    {
        // 使用dist查找待处理的点，类似于prim算法，对应dijstra_1的优化
        // 在dijstra_1里边，在每一轮对processV的处理，可能某些节点先处理然后又加入处理队列了
        // 比如说:1 -1-> 2 , 1 -3->3 , 2 -1-> 3 ,在这里从1到3最短是2
        // 下面就是优化这个过程的算法
        // 就是直接找到当前路径最短且不在closed数组里的节点
        // 对这个节点处理就能够避免上面的重复处理过程，对这个节点的信息处理完之后
        // 就把这个节点加入closed数组，表示该节点已经没有什么更有用的信息了
        // 总结:每次选取距离源点最近的未访问的（不在closed里)点，处理好之后加入closed数组，
        vector<int> dist(n + 1, INT_MAX);
        dist[1] = 0;
        vector<bool> closed(n + 1, false);
        auto findCurNode = [&]() -> int
        {
            // 选取距离源点最近的未访问的（不在closed里)点
            int resNode = 0;
            int resDist = INT_MAX;
            for (int node = 1; node <= n; ++node)
            {
                if (closed[node] == false && dist[node] < resDist)
                {
                    resDist = dist[node];
                    resNode = node;
                }
            }
            // 如果返回值是0，那么就是没找到，同时意味着循环结束
            return resNode;
        };
        int count = n;
        while (count--)
        {
            // 每次循环会选取一个节点来处理，处理好之后就加入closed数组，最多循环n次
            int curNode = findCurNode();
            if (curNode == 0)
                break;
            for (auto [v, w] : g[curNode])
            {
                if (dist[curNode] + w < dist[v])
                {
                    dist[v] = dist[curNode] + w;
                }
            }
            closed[curNode] = true;
        }
        cout << (dist[n] == INT_MAX ? -1 : dist[n]);
    };

    auto dijstra_4 = [&]() -> void
    {
        // 使用优先级处理队列，dist越小的节点，其信息就更有价值
        // 排序靠后的节点也有价值，但是需要之后再考虑
        // 由于是处理队列，就不需要closed数组，直到队列为空，没有额外信息就退出
        struct pqNode
        {
            int node, dist;
        };
        struct mygreater
        {
            auto operator()(const pqNode &a, const pqNode &b) -> bool
            {
                return a.dist > b.dist;
            }
        };
        priority_queue<pqNode, vector<pqNode>, mygreater> pq{};
        pq.push({1, 0});
        vector<int> dist(n + 1, INT_MAX);
        dist[1] = 0;
        while (!pq.empty())
        {
            // 选取最有信息价值的节点
            auto [curNode, d] = pq.top();
            pq.pop();

            // 处理节点信息
            for (auto [v, w] : g[curNode])
            {
                if (d + w < dist[v])
                {
                    // 发生更新行为，该节点需要加入处理队列
                    dist[v] = d + w;
                    pq.push({v, dist[v]});
                }
            }
        }
        cout << (dist[n] == INT_MAX ? -1 : dist[n]);
    };

    dijstra_3();
    return 0;
}