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
    // 优化的方法：在每一轮的对每个边的松弛过程中，如果edge.u的距离是int_max，那么就可以直接跳过
    //      所以根据这个思路，可以对每一个dist进行排序，只对dist不是int_max的节点进行判断
    //      在这里我使用hashmap来快速检测上游节点是否存在

    unordered_map<int, pair<int, int>> distMap{};
    distMap[1] = {0, 0}; // 初始化前驱节点为0,起始节点的距离初始化为0
    bool updated = true;
    for (int i = 0; i < n - 1 && updated; ++i)
    {
        updated = false; // 每轮开始前重置
        for (const auto &edge : edges)
        {
            auto it_u = distMap.find(edge.u);
            if (it_u == distMap.end())
                continue; // u 不可达，跳过

            long long new_dist = it_u->second.first + edge.w;
            auto it_v = distMap.find(edge.v);

            if (it_v == distMap.end())
            {
                // v 首次被访问
                distMap[edge.v] = {new_dist, edge.u};
                updated = true;
            }
            else if (new_dist < it_v->second.first)
            {
                // 找到更短路径
                it_v->second.first = new_dist;
                it_v->second.second = edge.u;
                updated = true;
            }
        }
        // 如果本轮没有更新，说明已经收敛，提前退出
        if (!updated)
            break;
    }

    // 检测负权环
    // 只需要再遍历一次所有边，看是否还能松弛
    for (const auto &edge : edges)
    {
        auto it_u = distMap.find(edge.u);
        if (it_u == distMap.end())
            continue;

        auto it_v = distMap.find(edge.v);
        long long new_dist = it_u->second.first + edge.w;

        // 如果 v 不存在，或者新距离更小，说明存在负权环影响到了路径
        if (it_v == distMap.end() || new_dist < it_v->second.first)
        {
            cout << "unconnected" << endl; // 题目要求输出 unconnected 表示有负权环或不可达？通常负权环是无解
            return 0;
        }
    }

    auto it_n = distMap.find(n);
    if (it_n == distMap.end())
    {
        cout << "unconnected" << endl;
    }
    else
    {
        cout << it_n->second.first << endl;
    }

    return 0;
}