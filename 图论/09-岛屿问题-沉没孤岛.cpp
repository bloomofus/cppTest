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

void print_answer(vector<vector<int>> &g)
{
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
}

template <class T>
void print_array(vector<T> &arr)
{
#ifdef print
    for (auto ele : arr)
        cout << ele << " ";
    cout << endl;
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
    std::deque<vector<int>> q{};
    std::function<bool()> diffuse_bfs;
    diffuse_bfs = [&]()
    {
        // 这个bfs有返回值，如果没有返回值，就和前几个题一样,
        // 那么就是一开始那个最初节点把自己的信息传递给周围的陆地节点，让其有一个一致的索引
        // 但是有返回值就不一样了，在bfs的过程中，会修改isSwitch2Sea这个最初的变量
        // 从而根据当前的陆地索引以及isSwitch2Sea这个变量知道该索引的陆地的共同属性
        bool isSwitch2Sea = true;
        while (!q.empty())
        {
            // 由于是广搜，所以dq当成队列使用
            vector<int> cur = q.front();
            print_array(cur);
            q.pop_front();
            // 先看当前节点是不是陆地，如果是陆地并且没有被访问，再添加后续节点
            int i = cur[0];
            int j = cur[1];
            if (g[i][j] == 1 && !closed[i][j])
            {
                // 是陆地并且没有被访问
                flag[i][j] = current_idx;
                closed[i][j] = 1;
                if (i == 0 || j == 0 || i == n - 1 || j == m - 1)
                {
                    // 说明该节点在边上，不会被沉没
                    isSwitch2Sea = false;
                }
                if (j + 1 < m && g[i][j + 1] == 1)
                    q.push_back({i, j + 1});
                if (i + 1 < n && g[i + 1][j] == 1)
                    q.push_back({i + 1, j});
                if (j - 1 >= 0 && g[i][j - 1] == 1)
                    q.push_back({i, j - 1});
                if (i - 1 >= 0 && g[i - 1][j] == 1)
                    q.push_back({i - 1, j});
            }
        }
        return isSwitch2Sea;
    };
    unordered_map<int, int> map{}; // 岛屿的索引号与是否沉没的映射
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
                    q.push_back(vector<int>{i, j});
                    map[current_idx] = diffuse_bfs();
                }
            }
        }
    }
    print_mat(flag);
    print_mat(closed);
    for (int i = 0; i < n; ++i)
    {
        for (int j = 0; j < m; ++j)
        {
            if (g[i][j] == 1)
            {
                g[i][j] = (map[flag[i][j]] == true) ? 0 : 1;
            }
        }
    }
    print_answer(g);
    return 0;
}