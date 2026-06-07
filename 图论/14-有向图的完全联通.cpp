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
    // 主要看看这个邻接链表的构建方式
    // 之前节点为字符串，我使用的是map+listNode，map[str]=listNode*
    // 由于这里节点是数字，那么就可以使用vector+vector来构建

    // -- 输入数据 && 构建邻接链表
    int n, m; // n是节点数，m是行数
    cin >> n >> m;
    vector<vector<int>> g(n + 1, vector<int>{});
    for (int i = 0; i < m; ++i)
    {
        int node, nextNode;
        cin >> node >> nextNode;
        g[node].push_back(nextNode);
    }

    // -- bfs
    auto bfs = [&](int node) -> unordered_set<int>
    {
        // 输入一个节点，输出对应的可达节点
        unordered_set<int> closed{node}; // 里面的节点就是全部可达节点
        deque<int> processV{node};
        while (!processV.empty())
        {
            int curNodeNum = processV.size();
            while (curNodeNum--)
            {
                for (auto nextNode_ : g[processV.front()])
                {
                    // 把当前节点的其余可达节点加入处理队列
                    if (closed.find(nextNode_) == closed.end())
                    {
                        // 没找到，说明nextNode_没有被访问
                        closed.insert(nextNode_);
                        processV.push_back(nextNode_);
                    }
                }
                processV.pop_front();
            }
        }
        return closed;
    };

    auto bfs2 = [&](int node) -> unordered_set<int>
    {
        // 输入一个节点，输出对应的可达节点
        unordered_set<int> closed{node}; // 里面的节点就是全部可达节点
        deque<int> processV{node};
        while (!processV.empty())
        {
            int top = processV.front();
            processV.pop_front();
            for (auto nextNode_ : g[top])
            {
                // 把当前节点的其余可达节点加入处理队列
                if (closed.find(nextNode_) == closed.end())
                {
                    // 没找到，说明nextNode_没有被访问
                    closed.insert(nextNode_);
                    processV.push_back(nextNode_);
                }
            }
        }
        return closed;
    };

    auto dfs = [&](int node) -> unordered_set<int>
    {
        unordered_set<int> closed{node}; // 里面的节点就是全部可达节点
        deque<int> processV{node};
        while (!processV.empty())
        {
            int top = processV.back();
            processV.pop_back();
            for (auto nextNode_ : g[top])
            {
                // 把当前节点的其余可达节点加入处理队列
                if (closed.find(nextNode_) == closed.end())
                {
                    // 没找到，说明nextNode_没有被访问
                    closed.insert(nextNode_);
                    processV.push_back(nextNode_);
                }
            }
        }
        return closed;
    };

    // -- 主循环
    unordered_set<int> reachNodes = bfs(1);
    for (int i = 1; i <= n; ++i)
    {
        if (reachNodes.find(i) == reachNodes.end())
        {
            cout << -1;
            return 0;
        }
    }
    cout << 1;
    return 0;
}