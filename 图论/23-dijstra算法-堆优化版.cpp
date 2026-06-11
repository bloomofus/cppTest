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

    struct distClass
    {
        int dist;
        int node;
    };
    auto greater = [](const distClass &a, const distClass &b)
    {
        // greater是从前往后逐渐变大
        return a.dist > b.dist;
    };
    priority_queue<distClass, vector<distClass>, decltype(greater)> pq(greater);
    vector<vector<int>> dist_mat(n + 1, vector<int>{INT_MAX, 0}); // 第一列是dist，第二列是前驱节点
    dist_mat[1][0] = 0;                                           // 节点1的前驱节点假装是0
    unordered_set<int> closed{};
    pq.push({0, 1}); // 加入第一个节点
    while (!pq.empty())
    {
        auto processNode = pq.top();
        pq.pop();
        // 需要判断当前处理类是否已经处理过
        if (closed.find(processNode.node) != closed.end())
            continue;

        // 接下来对于这个processNode的出度进行遍历，并且更新dist_mat矩阵里的距离信息
        for (auto edge : g[processNode.node])
        {
            int next_node = edge.first;
            int edge_w = edge.second;
            if (closed.find(next_node) == closed.end() &&
                dist_mat[next_node][0] > dist_mat[processNode.node][0] + edge_w)
            {
                // 从当前的处理节点到next_node的距离比之前记录的更近
                dist_mat[next_node][0] = dist_mat[processNode.node][0] + edge_w;
                dist_mat[next_node][1] = processNode.node; // 更新前驱节点
                // 更新前驱节点之后需要把该节点加入处理队列
                pq.push({dist_mat[next_node][0], next_node});
            }
        }
        closed.insert(processNode.node);
    }
    cout << (dist_mat[n][0] == INT_MAX ? -1 : dist_mat[n][0]);
    return 0;
}