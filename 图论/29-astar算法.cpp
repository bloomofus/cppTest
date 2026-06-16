#include <bits/stdc++.h>
using namespace std;

int main()
{
    // -- 思路
    // astar算法和bfs其实是有点类似的，bfs每次拓宽搜索的范围
    // 然后将探索的新节点纳入处理队列，然后对这个队列进行处理
    // 在while(!queue.empty())这个循环中，不断处理队列起始的节点，然后将新探索的节点加入到队尾
    // 所以bfs最核心的就是一个普通的队列
    // astar算法在此基础上只不过是将这个队列转变为优先级队列而已
    // 使得更有可能接近目标节点的节点能够有限处理
    // 其余的部分基本上是一样的
    // 为什么f=g+h，这里的g不是预测距离呢？因为这个是可知的，而h你只能预测

    // -- 输入数据
    int n;
    cin >> n;
    struct Point
    {
        int x, y;

        auto testAction(const Point &action) -> pair<bool, Point>
        {
            int x_new = x + action.x;
            int y_new = y + action.y;
            if (x_new >= 1 && x_new <= 1000 && y_new >= 1 && y_new <= 1000)
            {
                // 合法的位置
                return {true, {x_new, y_new}};
            }
            else
                return {false, {0, 0}};
        }

        auto operator==(const Point &other) -> bool
        {
            return x == other.x && y == other.y;
        }
    };
    struct Plan
    {
        Point start, end;
    };
    vector<Plan> plans{};
    for (int i = 0; i < n; ++i)
    {
        int a, b, c, d;
        cin >> a >> b >> c >> d;
        plans.push_back({{a, b}, {c, d}});
    }

    vector<Point> actions{{1, 2}, {2, 1}, {2, -1}, {1, -2}, {-1, -2}, {-2, -1}, {-2, 1}, {-1, 2}};

    struct pqNode
    {
        int x, y, step;
        float dist, cost;

        pqNode() = delete; // 删除默认构造函数，必须以指定的构造函数构造
        pqNode(const Point &curPos, const Point &endPos, int curSteps_in)
        {
            // curSteps_in是指从开始节点到达当前节点的需要的步数
            x = curPos.x;
            y = curPos.y;
            step = curSteps_in;
            dist = getDist(curPos, endPos);
            cost = curSteps_in + dist;
        }

        auto getPos() -> Point
        {
            return {x, y};
        }

        static auto getDist(const Point &p1, const Point &p2) -> float
        {
            // 返回欧氏距离
            float dx = p1.x - p2.x;
            float dy = p1.y - p2.y;
            return sqrt(dx * dx + dy * dy);
        };
    };

    auto getMinStep = [&](Point &start, Point &end) -> int
    {
        vector<vector<bool>> closed(1001, vector<bool>(1001, false));

        struct mycmp
        {
            // 传入优先级队列，使得cost较小的排在前面
            auto operator()(const pqNode &node1, const pqNode &node2) -> bool
            {
                return node1.cost > node2.cost;
            }
        };
        priority_queue<pqNode, vector<pqNode>, mycmp> pq;
        pq.push(pqNode(start, end, 0));
        while (!pq.empty())
        {
            // 先从队列取一个节点，如果就是目标位置，则直接返回该节点的step属性
            // 如果不是目标位置，则进行各个方向的拓展，需要判断边界
            // 将拓展后的节点加入队列
            // 新节点有可能与之前的节点重合，这个时候留下花费更少的节点
            pqNode curNode = pq.top();
            pq.pop(); // 访问该节点，然后将该节点加入closed数组

            if (closed[curNode.x][curNode.y] == true)
                continue;
            else
                closed[curNode.x][curNode.y] = true;

            if (curNode.getPos() == end)
            {
                // 刚好是目标位置
                return curNode.step;
            }
            else
            {
                // 不是目标位置，需要四面八方扩展
                for (auto action : actions)
                {
                    auto [isValid, newPos] = curNode.getPos().testAction(action);
                    if (isValid && closed[newPos.x][newPos.y] == false)
                    {
                        // 位置有效
                        // 需要判断是否已经处理过了
                        pq.push({newPos, end, curNode.step + 1});
                    }
                }
            }
        }
        cout << "???";
        return -999;
    };
    for (int i = 0; i < n; ++i)
    {
        auto plan = plans[i];
        cout << getMinStep(plan.start, plan.end) << (i == n - 1 ? "" : "\n");
    }
    return 0;
}