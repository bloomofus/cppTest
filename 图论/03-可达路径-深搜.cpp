#include "core.h"
#include "utils/myclass.h"
#include "mystruct/mytree.h"

using namespace std;
using namespace mystruct;

#define print

void dfs(vector<vector<int>> &g, int node, vector<int> &path, vector<vector<int>> &paths)
{
    if (node == g.size() - 1)
    {
        // 先看当前节点是不是目标节点
        paths.push_back(path);
        return;
    }
    // 当前节点不是目标节点，遍历其子节点
    for (int i = 1; i <= g.size(); ++i)
    {
        if (g[node][i] == 1)
        {
            // 两个节点连接
            path.push_back(i);
            dfs(g, i, path, paths);
            path.pop_back();
        }
    }
}

void print_path(vector<vector<int>> &paths)
{
    if (paths.size() == 0)
    {
        cout << -1 << endl;
        return;
    }
    for (auto path : paths)
    {
        for (auto node : path)
        {
            cout << node;
            if (node != path.back())
            {
                cout << " ";
            }
        }
        cout << endl;
    }
}

int main()
{
    // -- 思路
    // 这道题虽然是深搜或者广搜就能够实现，但是难点就在于如何取记录途径点
    // 记录途径点的常用方法是回溯算法，本体也是用这个思路
    // 回溯算法一般是深搜
    // 假设我现在在一个起始节点，我有很多下游节点
    // 那么我下一步就是需要去遍历这些下游节点
    // 但是在此之前，我需要先记录本身这个起始节点作为路径开始
    // 遍历下游节点的时候，在循环里，我需要先把该节点加入路径->遍历该节点的下游节点（处理完毕返回）->路径弹出该节点
    // 就这样就记录好了对应的路径
    // 当我找到想要的路径之后，把这个路径存储一下即可
    // -- 思考
    // 为什么不使用closed数组？因为是简单无环图，如果有环就需要考虑，不过这个情况比较复杂。如果是普通的bfs或者dfs
    //      去遍历每个节点的元素的话，不能重复遍历，这个时候就需要closed数组。但是回溯算法作为一种特殊的dfs，其需要记录路径
    //      所以必须保留中间节点。
    // dfs的形式？1，递归或者回溯算法，2，栈存储处理节点，直到栈为空
    // bfs的形式？1，队列存储处理节点，直到队列为空，2，层序循环

    int n = 0;
    int m = 0;
    cin >> n >> m;
    vector<vector<int>> g(n + 1, vector<int>(n + 1, 0));
    for (int i = 0; i < m; ++i)
    {
        int father;
        int child;
        cin >> father >> child;
        g[father][child] = 1;
    }
    vector<int> path{};
    vector<vector<int>> paths{};

    path.push_back(1);
    dfs(g, 1, path, paths);
    print_path(paths);
    return 0;
}