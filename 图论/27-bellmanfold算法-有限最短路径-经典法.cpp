#include <bits/stdc++.h>
using namespace std;

int main()
{
    // -- 思路
    // 经典法，对每个边进行松弛，可以直接有效地控制松弛轮次

    // -- 输入数据
    int n, m;
    cin >> n >> m;
    struct Edge{ int u,v,w;};
    vector<Edge> edges{};
    for(int i=0;i<m;++i)
    {
        int a,b,c;
        cin>>a>>b>>c;
        edges.push_back({a,b,c});
    }
    int src,dst,k;
    cin>>src>>dst>>k;

    // -- bellmanfold算法-有限最短路径
    vector<int> dist(n+1,INT_MAX);
    dist[src]=0;

    for(int i=0;i<k+1;++i)
    {
        bool update=false;
        vector<int> nextDist = dist;
        for (auto [u, v, w] : edges)
        {
            // 如果上游节点的dist为INT_MAX，则跳过
            if(dist[u]==INT_MAX) continue;
            if(dist[u]+w<dist[v])
            {
                nextDist[v] = dist[u] + w;
                update=true;
            }
        }
        dist = nextDist;
        if (!update)
            break;
    }

    cout<<(dist[dst]==INT_MAX?"unreachable":to_string(dist[dst]));
    
    return 0;
}