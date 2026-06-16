#include <bits/stdc++.h>
using namespace std;

int main()
{
    // -- 思路

    // -- 输入数据
<<<<<<< HEAD
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
        g[a].push_back({a,b, c});
        edges.push_back({a, b, c});
        // 如果是无向图，添加反向边（权重也是 c，不是 -c！）
        // g[b].push_back({b,a, c});
    }
    int src, dst, k;
    cin >> src >> dst >> k;

    // -- bellmanfold 算法
    queue<int> processV{};
    processV.push(src);
    vector<bool> inQueue(n + 1, false);
    inQueue[src] = true;
    vector<int> count(n + 1, 0);
    vector<vector<int>> distMat(n + 1, vector<int>(n + 1, INT_MAX));
    distMat[src][0] = 0;
    vector<int> minDist(n + 1, INT_MAX);
    minDist[src] = 0;
    auto locateK = [&](int curDist, int targetNode) -> int
    {
        for (int i = 0; i < n + 1;++i)
        {
            if(distMat[targetNode][i]==curDist)
                return i;
        }
        cout << " not found ???" << endl;
        return -1;
    };
    while (!processV.empty())
    {
        // 当前上游节点
        int curNode = processV.front();
        processV.pop();
        inQueue[curNode] = false;

        // 对当前上游节点的每一个边进行松弛
        for(auto edge:g[curNode])
        {
            int from = edge.u;
            int to = edge.v;
            int weight = edge.w;
            if(minDist[from]+weight<minDist[to])
            {
                // 需要松弛
                int cur_k = locateK(minDist[from], from) + 1; // 从src->to的中间节点数
                distMat[to][cur_k] = minDist[from] + weight;
                minDist[to] = distMat[to][cur_k];
                // 如果该下游节点已经松弛了，那么其下下游节点也有可能更新松弛
                // 所以需要把该下游节点加入处理列表
                // 如果从src->to的中间节点数量以及到了k，那么就不需要把下游节点加入处理列表了
                if(cur_k-1>k) continue;
                if (!inQueue[to])
                {
                    processV.push(to);
                    inQueue[to] = true;
                    count[to]++;
                    if (count[to] >= n)
                    {
                        // 说明陷入负权环的圈子里了
                        // 加入一次处理列表就是松弛了一下，从1->to这个路线最多松弛v-1下
                        cout << "circle";
                        // 不需要直接退出，因为即使有负权环，在这个问题下也可以利用之前跑的数据
                        // 有前面的cur_k限制，一般不会运行到这
                        return 0;
                    }
                }
            }
        }

    }

    cout << (distMat[dst][k+1] == INT_MAX ? "unconnected" : to_string(distMat[dst][k+1]));

=======
    int n;
    cin>>n;
    struct Point
    { 
        int x,y;
        auto takeAction(Point& action)->Point{
            x+=action.x;
            y+=action.y;
            return {x,y};
        }    
        auto testAction(Point& action)->Point{
            return {x+action.x,y+action.y};
        }
        auto getDist(const Point& target, int choice = 1) const -> float {
            float ans = 0.0f;
        
            // 提前计算差值，避免重复减法，并转为 float 防止整数溢出
            float dx = static_cast<float>(target.x - x);
            float dy = static_cast<float>(target.y - y);

            switch (choice) {
                case 1:
                    // 曼哈顿距离: |dx| + |dy|
                    // 使用 fabs 处理浮点数绝对值，或者直接利用 dx,dy 已转浮点的特性
                    ans = std::fabs(dx) + std::fabs(dy);
                    break;
                case 2:
                    // 欧氏距离: sqrt(dx^2 + dy^2)
                    // 修复：加上 sqrt
                    ans = std::sqrt(dx * dx + dy * dy);
                    break;
                default:
                    // 可选：抛出异常或返回 -1 表示错误
                    break;
            }
            return ans;
        }

        auto operator==(Point& other)->bool{
            return x==other.x&&y==other.y;
        }
        auto operator!=(Point& other)->bool{
            return x!=other.x||y!=other.y;
        }
    };
    struct Plan{Point start,end;};
    vector<Plan> plans{};
    for(int i=0;i<n;++i)
    {
        int a,b,c,d;
        cin>>a>>b>>c>>d;
        plans.push_back({{a,b},{c,d}});
    }

    vector<Point> actions{{1,2},{2,1},{2,-1},{1,-2},{-1,-2},{-2,-1},{-2,1},{-1,2}};


    auto getMinStep=[&](Point& start,Point& end)->int{
        vector<vector<int>> minSteps(1001,vector<int>(1001,999999/2));
        minSteps[start.x][start.y]=0;
        int ansSteps=0;
        Point cur=start;
        while(cur!=end)
        {
            float minCost=999999;
            Point mayPos{0,0};
            for(auto action:actions)
            {
                Point newPos=cur.testAction(action);
                if(newPos.x>=1&&newPos.x<=1000&&newPos.y>=0&&newPos.y<=1000)
                {
                    float newPosCost=minSteps[newPos.x][newPos.y]+newPos.getDist(end,1);
                    if(newPosCost<minCost)
                    {
                        mayPos=newPos;
                    }
                }
            }
            cur=mayPos;
            ++ansSteps;
            minSteps[mayPos.x][mayPos.y]=ansSteps;
        }
        return ansSteps;
    };
    for(int i=0;i<n;++i)
    {
        auto plan=plans[i];
        cout<<getMinStep(plan.start,plan.end)<<(i==n-1?"":"\n");
    }
>>>>>>> 13ff643767fdc159ece753ca3cc301dd1e8b75ac
    return 0;
}