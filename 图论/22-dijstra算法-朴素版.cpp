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
    // Dijkstra 算法的核心思想是贪心策略：
    // 每次从未确定最短路的节点中选取距离起点最近的节点，并用它来更新其邻居节点的距离，从而逐步确定所有节点的最短路径。
    vector<int> closed(n + 1, false);
    vector<int> dist(n + 1, INT_MAX);
    dist[1] = 0;
    auto findCurNode = [&closed, &dist, &n]() -> pair<int, int>
    {
        // 找出当前最小dist的节点，并且该节点还要没有加入closed
        // 如果输出node为0，那么就是没有找到，所有的节点就已经遍历结束了
        // 如果输出node不是0，如果输出dist不是INT_MAX，说明该节点还有后续节点
        // 如果输出node不是0，如果输出dist是INT_MAX，说明该节点是浮空节点，和其他节点无法连接
        int min_dist = INT_MAX;
        int curNode = 0;
        for (int i = 1; i <= n; ++i)
        {
            if (closed[i] == false && dist[i] < min_dist)
            {
                curNode = i;
                min_dist = dist[i];
            }
        }
        return {curNode, min_dist};
    };
    int tmp = n; // 每次循环会给一个节点加入closed数组，最多循环n次
    while (1)
    {
        // 控制循环出去的方法
        // 1,int tmp = n; while(tmp--) 每次循环会给一个节点加入closed数组，最多循环n次
        // 2,auto [curNode,dist_] = findCurNode(); if (dist_ == INT_MAX) break; 找到悬空节点
        auto [curNode, dist_] = findCurNode();
        if (dist_ == INT_MAX)
            break;
        closed[curNode] = true;
        // if (g[curNode].size()==0) break; // 说明无法继续探索了,这个是错误的❌
        for (auto [next_node, edge_w] : g[curNode])
        {
            // 在这个循环里面，是根据已知的最短路径更新所有未访问节点的dist信息，但是并不涉及closed数组
            if (closed[next_node] == false && dist[curNode] + edge_w < dist[next_node])
            {
                // 当前next_node节点没有被访问，并且从curNode到达next_node花费更少
                dist[next_node] = dist[curNode] + edge_w;
            }
        }
    }
    cout << (dist[n] == INT_MAX ? -1 : dist[n]);
    return 0;
}