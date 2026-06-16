#include <bits/stdc++.h>
using namespace std;

// #define debug

#ifdef debug
#define dbg cout << "[DEBUG] " << __FILE__ << ":" << __LINE__ << endl;
#else
#define dbg ;
#endif

// -- tools
// 辅助函数：获取整数转换为字符串后的长度
int get_digit_width(int val)
{
    string s = to_string(val);
    return s.length();
}

// 模板版本：打印一维数组（支持指定宽度）
template <typename T>
void print_arr(const vector<T> &arr, int width)
{
    cout << "[";
    for (size_t i = 0; i < arr.size(); ++i)
    {
        if (i > 0)
            cout << ", ";
        // setw(width) 设置最小宽度，right 表示右对齐（数字通常右对齐更整齐）
        cout << setw(width) << arr[i];
    }
    cout << "]";
}

// 模板版本：打印二维数组（矩阵）- 自动计算最大宽度并对齐
template <typename T>
void print_mat(const vector<vector<T>> &mat)
{
    if (mat.empty())
    {
        cout << "[]" << endl;
        return;
    }

    // 1. 遍历所有元素，找到最大数字的字符串长度
    int max_width = 1;
    for (const auto &row : mat)
    {
        for (const auto &val : row)
        {
            int w = get_digit_width(val);
            if (w > max_width)
                max_width = w;
        }
    }

    // 为了美观，可以额外加1个空格 padding
    max_width += 1;

    cout << "[" << endl;
    for (const auto &row : mat)
    {
        cout << "  "; // 行首缩进
        print_arr(row, max_width);
        cout << endl;
    }
    cout << "]" << endl;
}

int main()
{
    // -- 思路

    // -- 输入数据
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
        // 如果是无向图，添加反向边（权重也是 c，不是 -c！）
        // g[b].push_back({b,a, c});
    }

    // -- bellmanfold 算法
    // bellmanfold算法的核心思想是先初始化距离为0，
    // 然后对每一个边松弛v-1次，从而得到所有节点之间的最短路径
    // 松弛之后，再松弛一轮检测负权环
    // 最核心的两个数据对象是：1，边列表，2，距离表
    // 优化的方法：这里使用队列优化的方法，原来的版本是对每一个边进行v-1轮松弛
    //      但是有很多无用功，所以，把需要进行处理的上游节点都加入一个队列里面
    //      只对队列里的节点的边进行松弛，一开始队列里面只有1这个节点
    //      然后把1的所有边进行松弛之后，把新的节点加入处理队列
    //      就是通过已经初始化的节点，将其下游节点初始化，顺便对这个路线进行一次松弛（初始化和更新都是松弛）
    //      比如把1处理好之后，把2、3节点加入处理列表，这个过程对1->2以及1->3的路线进行了一次松弛
    //      然后按顺序把2、3处理好之后，2、3弹出再把别的，比如说4加入处理列表，那么就是把2->4的路线进行了一次松弛
    //      下游节点加入处理列表一次，就是把from->to的路线进行一次松弛
    //      2，3弹出之后并不意味着2、3已经找到了最短路径
    //      如果我现在遍历到了5节点，5有下游节点2，并且此时，在遍历5->2这个路线的时候松弛了
    //      那就是说，从1->2有更短的路径（经过5的那条路径1->5->2），
    //      那么从2开始到2的下游节点，是不是也可能有更短的路径
    //      因此需要把2加入处理队列
    //      如果5->3这个路线没有松弛，说明3这个节点我之前遍历的时候就已经找到比较短的路径了
    //      此时再把3加入处理队列，无异于做无用功，所以不添加

    queue<int> processV{};
    processV.push(1);
    vector<bool> inQueue(n + 1, false);
    inQueue[1] = true;
    vector<int> count(n + 1, 0);
    vector<int> dist(n + 1, INT_MAX);
    dist[1] = 0;
    while (!processV.empty())
    {
        // 当前上游节点
        int curNode = processV.front();
        processV.pop();
        inQueue[curNode] = false;

        // 对当前上游节点的每一个边进行松弛
        for (auto edge : g[curNode])
        {
            int from = edge.u;
            int to = edge.v;
            int weight = edge.w;
            if (dist[from] + weight < dist[to])
            {
                // 需要松弛
                dist[to] = dist[from] + weight;
                // 如果该下游节点已经松弛了，那么其下下游节点也有可能更新松弛
                // 所以需要把该下游节点加入处理列表
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
                        return 0;
                    }
                }
            }
        }
    }

    cout << (dist[n] == INT_MAX ? "unconnected" : to_string(dist[n]));

    return 0;
}