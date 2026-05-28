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
    std::deque<vector<int>> st{};
    std::function<void()> diffuse_dfs;
    diffuse_dfs = [&]()
    {
        while (!st.empty())
        {
            // 由于是深搜，所以dq当成stack使用
            vector<int> cur = st.back();
            print_array(cur);
            st.pop_back();
            // 先看当前节点是不是陆地，如果是陆地并且没有被访问，再添加后续节点
            int i = cur[0];
            int j = cur[1];
            if (g[i][j] == 1 && !closed[i][j])
            {
                // 是陆地并且没有被访问
                flag[i][j] = current_idx;
                closed[i][j] = 1;
                if (j + 1 < m && g[i][j + 1] == 1)
                    st.push_back({i, j + 1});
                if (i + 1 < n && g[i + 1][j] == 1)
                    st.push_back({i + 1, j});
                if (j - 1 >= 0 && g[i][j - 1] == 1)
                    st.push_back({i, j - 1});
                if (i - 1 >= 0 && g[i - 1][j] == 1)
                    st.push_back({i - 1, j});
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
                    st.push_back(vector<int>{i, j});
                    diffuse_dfs();
                }
            }
        }
    }
    print_mat(flag);
    print_mat(closed);
    cout << current_idx;
    return 0;
}