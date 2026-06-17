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
    // -- 思路
    // 从上到下从左到右逐个遍历格子，如果当前遍历的格子是海洋，那么就直接跳过
    // 如果是陆地，那么就扩散似的标记周围所有的陆地，这个过程使用dfs或者bfs都可以，最好是标记上对应的岛屿编号
    // 如果遍历到该格子发现已经有岛屿编号了，那么就是已经遍历过了，就跳过不处理
    // 这样就能找到所有的岛屿，并且对其进行编号
    // 编号的数组是flag，处理已经处理好的数组是closed，实际上flag也可以代表closed处理
    // -- 思考
    // 并查集？这类处理是否在一个集合的问题适合使用并查集处理，当我们遍历到一个没有标记过的陆地的时候
    //      可以初始化一个并查集uf，然后将其周围的陆地都使用uf.union()加入到并查集里面，
    //      当然这里也要使用递归或者bfs/dfs，也需要使用closed数组
    //      但是不太适合这个问题的情况,并查集可以检测任意两个格子是否在一个岛屿上，
    //      但是不太好检测岛屿个数，只能通过看看并查集初始化的数量来判断岛屿数量。
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