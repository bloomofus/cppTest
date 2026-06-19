#include <bits/stdc++.h>
using namespace std;

int main()
{
    // -- 思路
    // bellmanfold原理：松弛v-1次能够找到从起始节点经过v-1条边的最短路径
    // 传统的bellmanfold算法是对边进行v-1次循环遍历，每一轮循环需要遍历每一条边
    // 循环结束之后，在循环一次看看有没有更新，如果有更新事件，那么就是有负权环
    // 但是这个方法重复计算很多，当遍历一个边的时候，如果上游节点的dist是int_max，
    // 那么本次松弛就没用必须跳过，但是每轮循环又必须对每一条边进行遍历
    // 所以将节点dist不是int_max的节点集中放到一个处理队列里，就能够极大提高效率
    //
    // bellmanfold的算法核心还是我之前讲的信息理论
    // 一个起始节点的距离是0，那么这个节点在遍历之前具有一定的信息
    // 通过遍历该节点的各个边的时候，能够将信息取出来传递给下游节点
    // 那么此时本节点的信息暂时就没啥用了，因为已经用过了
    // 但是下游节点因为更新了dist值，所以有一个新的信息
    // 所以下游节点就需要加入处理队列
    // 但是遍历着遍历着，之前遍历过的节点的dist更新了
    // 那么就需要重新将该节点加入处理队列
    // 所以处理的时候不需要closed数组，但是需要InQueue，防止一个处理队列里面有几个重复的节点
    // 所以核心就是：dist更新->下游节点变得有信息->加入处理队列
    // 通过下面的两个算法的比较，也可以看出，轮次控制遍历的时候，可以使用update来提前结束循环
    // 但是对于单个节点的遍历的时候，就不可以
    int n, m;
    cin >> n >> m;
    struct Edge
    {
        int u, v, w;
    };
    vector<vector<Edge>> g(n + 1); // 邻接表：g[u] = {(v, w), ...} 表示从 u 到 v 权重为 w
    vector<Edge> edges{};
    for (int i = 0; i < m; ++i)
    {
        int a, b, c;
        cin >> a >> b >> c;
        g[a].push_back({a, b, c});
        edges.push_back({a, b, c});
    }

    auto bellmanfold_0 = [&]() -> void
    {
        // 经典法，进行v-1轮对每条边进行松弛
        vector<int> dist(n + 1, INT_MAX);
        dist[1] = 0;
        int round = n - 1;
        while (round--)
        {
            bool update = false;
            for (auto [u, v, w] : edges)
            {
                if (dist[u] != INT_MAX && dist[u] + w < dist[v])
                {
                    // 发生更新事件
                    dist[v] = dist[u] + w;
                    update = true;
                }
            }
            if (!update)
                break;
        }

        //
        bool update = false;
        for (auto [u, v, w] : edges)
        {
            if (dist[u] != INT_MAX && dist[u] + w < dist[v])
            {
                // 发生更新事件
                dist[v] = dist[u] + w;
                update = true;
            }
            if (update)
                break;
        }

        if (update)
        {
            // 有负权环
            cout << "circle";
        }
        else
            cout << (dist[n] == INT_MAX ? "unconnected" : to_string(dist[n]));
    };

    auto bellmanfold_1 = [&]() -> void
    {
        // 使用轮次控制的bellmanfold算法
        queue<int> processV{};
        processV.push(1);
        vector<bool> inQueue(n + 1, false);
        inQueue[1] = true;
        vector<int> dist(n + 1, INT_MAX);
        dist[1] = 0;
        vector<int> count(n + 1, 0);
        while (!processV.empty())
        {
            int curSize = processV.size();
            bool update = false;
            while (curSize--)
            {
                int curNode = processV.front();
                processV.pop();
                inQueue[curNode] = false;
                for (auto [u, v, w] : g[curNode])
                {
                    int newDist = dist[curNode] + w;
                    if (newDist < dist[v])
                    {
                        // 发生更新事件，下游节点需要加入处理队列
                        dist[v] = newDist;
                        count[v]++;
                        update = true;
                        if (!inQueue[v])
                        {
                            // 如果已经在队列里，上边dist[v] = newDist;已经实现距离的更新所以不处理即可
                            // 如果不在，那么就需要加入处理队列
                            // 如果不使用inQueue数组，那么就会重复把该节点加入处理队列，虽然不会报错，但是会有很多重复的判断
                            processV.push(v);
                            inQueue[v] = true;
                        }
                        if (count[v] >= n)
                        {
                            // count数组是必要的，不然程序会持续的搜寻下去
                            // 陷入负权环
                            cout << "circle";
                            return;
                        }
                    }
                }
            }
            if (!update)
                break;
        }
        cout << (dist[n] == INT_MAX ? "unconnected" : to_string(dist[n]));
    };

    auto bellmanfold_2 = [&]() -> void
    {
        // 使用单节点控制的bellmanfold算法
        queue<int> processV{};
        processV.push(1);
        vector<bool> inQueue(n + 1, false);
        inQueue[1] = true;
        vector<int> dist(n + 1, INT_MAX);
        dist[1] = 0;
        vector<int> count(n + 1, 0);
        while (!processV.empty())
        {
            int curNode = processV.front();
            processV.pop();
            inQueue[curNode] = false;
            for (auto [u, v, w] : g[curNode])
            {
                int newDist = dist[u] + w;
                if (newDist < dist[v])
                {
                    // 发生更新事件
                    dist[v] = newDist;
                    count[v]++;

                    if (!inQueue[v])
                    {
                        processV.push(v);
                        inQueue[v] = true;
                    }
                    if (count[v] >= n)
                    {
                        // 陷入负权环
                        cout << "circle";
                        return;
                    }
                }
            }
        }
        cout << (dist[n] == INT_MAX ? "unconnected" : to_string(dist[n]));
    };

    bellmanfold_0();

    return 0;
}