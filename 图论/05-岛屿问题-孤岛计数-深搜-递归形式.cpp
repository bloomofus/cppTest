#include <bits/stdc++.h>
using namespace std;

#define dbg cout << "debug here" << endl;
// #define print

template <class T>
void print_mat(vector<vector<T>> &g)
{
#ifdef print
    for (int i = 0; i < g.size(); ++i)
    {
        for (int j = 0; j < g[i].size(); ++j)
        {
            cout << g[i][j];
            if (j != g[i].size() - 1)
            {
                cout << " ";
            }
        }
        cout << endl;
    }
#endif
}

int main()
{
    int n = 0;
    int m = 0;
    cin >> n >> m;
    vector<vector<int>> g(n, vector<int>(m, 0));
    for (int i = 0; i < n; ++i)
    {
        for (int j = 0; j < m; ++j)
        {
            cin >> g[i][j];
        }
    }
    vector<vector<int>> flag(n, vector<int>(m, -1));
    vector<vector<bool>> closed(n, vector<bool>(m, 0));
    print_mat(g);

    int current_idx = 0;

    std::function<void(int, int)> diffuse_dfs;
    diffuse_dfs = [&](int i, int j)
    {
        if (i >= 0 && i < n && j >= 0 && j < m)
        {
            if (closed[i][j] == 1)
            {
                return;
            }
            if (g[i][j] == 0)
            {
                closed[i][j] = 1; // 海洋部分是否加入closed并不重要
                return;
            }
            else
            {
                // 当前节点是陆地
                flag[i][j] = current_idx;
                closed[i][j] = 1;
                diffuse_dfs(i, j + 1);
                diffuse_dfs(i + 1, j);
                diffuse_dfs(i, j - 1);
                diffuse_dfs(i - 1, j);
            }
        }
    };

    for (int i = 0; i < n; ++i)
    {
        for (int j = 0; j < m; ++j)
        {
            if (g[i][j] == 1)
            {
                if (closed[i][j] == 1)
                {
                    // 一般来说，通过这个循环遍历到的陆地都是独立的岛屿
                    // 如果它和之前的岛屿有连接，那么在之前那个岛屿递归的时候就会蔓延到当前这个岛屿
                    // 所以不存在当前岛屿既和之前岛屿有连接，又是在这个循环里面遍历到的
                    continue;
                }
                else
                {
                    ++current_idx;
                    diffuse_dfs(i, j);
                }
            }
        }
    }
    print_mat(flag);
    print_mat(closed);
    cout << current_idx;
    return 0;
}