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
    // 第一轮更新，能够找到起始节点使用一条边相连的节点
    // 第二轮更新，能找到与起始节点两条边相连的节点
    // 以此类推

    vector<vector<int>> distMat(n + 1, {INT_MAX, 0}); // 初始化前驱节点为0
    distMat[1][0] = 0;                                // 起始节点的距离初始化为0
    for (int i = 0; i < n - 1; i++)
    {
        for (auto edge : edges)
        {
            if (distMat[edge.u][0] != INT_MAX && distMat[edge.u][0] + edge.w < distMat[edge.v][0])
            {
                // 找到更短路径
                distMat[edge.v][0] = distMat[edge.u][0] + edge.w;
                distMat[edge.v][1] = edge.u;
            }
        }
    }

    // 检测负权环
    for (auto edge : edges)
    {
        if (distMat[edge.u][0] != INT_MAX && distMat[edge.u][0] + edge.w < distMat[edge.v][0])
        {
            // 找到更短路径,说明有负权环
            cout << "unconnected";
            return 0;
        }
    }
    if (distMat[n][0] == INT_MAX)
        cout << "unconnected";
    else
        cout << distMat[n][0];
    return 0;
}