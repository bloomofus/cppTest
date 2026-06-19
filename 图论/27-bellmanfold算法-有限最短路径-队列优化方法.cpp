#include <bits/stdc++.h>
using namespace std;
int main()
{
    // -- 思路
    // 这个是队列优化的方法，一开始的队列里面只有初始节点，通过对初始节点的每个边进行松弛，
    // 就能得到距离初始节点一条边的最短路径可以到达的节点
    // 由于初始节点的下游节点更新了更短的路径，所以需要把其加入处理队列
    // 但是要根据循环轮次依次添加，从而实现获取松弛n次从开始节点的最短路径

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
    int src,dst,k;
    cin>>src>>dst>>k;

    // -- bellmanfold算法-有限最短路径
    queue<int> processV{};
    processV.push(src);
    vector<int> dist(n+1,INT_MAX);
    dist[src]=0;

    for(int i=0;i<=k;++i)
    {
        queue<int> tmpNewProcessV{};
        vector<int> tmpDist=dist;
        vector<bool> inQueue(n+1,false); // 这个必须在循环内初始化，因为只对tmpNewProcessV生效

        while(!processV.empty())
        {
            // 遍历这个处理队列
            auto u=processV.front();
            processV.pop();

            // 如果当前节点距离是无穷大，跳过
            // if (dist[u] == INT_MAX) continue; // 由于这里是队列优化的版本，所以一般不会出现这种情况

            for(auto [v,w]:g[u])
            {
                // 遍历上游节点的每一条边
                long long newDist = (long long)dist[u] + w;
                if(newDist<tmpDist[v])
                {
                    // 到v节点有更短的路径，所以需要把v加入处理队列
                    if(!inQueue[v])
                    {
                        tmpNewProcessV.push(v);
                        inQueue[v]=true;
                    }
                    tmpDist[v]=newDist;
                }
            }
        }
        dist=tmpDist;
        processV=tmpNewProcessV;
    }

    cout<<(dist[dst]==INT_MAX?"unreachable":to_string(dist[dst]));
    
    return 0;
}