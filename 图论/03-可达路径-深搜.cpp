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