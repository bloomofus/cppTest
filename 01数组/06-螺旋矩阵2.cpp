#include <bits/stdc++.h>
using namespace std;

class Solution
{
public:
    vector<vector<int>> generateMatrix(int n)
    {
        // -- 思路
        // 可以使用四个向量表示下一个位置的方向，然后判断每次碰壁之后的方向
        // 就是对应的方向向量索引++，然后取模一下
        // 如果修改好方向之后的下一个位子已经被填充了，那么就退出循环
        vector<vector<int>> mat(n, vector<int>(n, 0));
        vector<vector<int>> dirs{{0, 1}, {1, 0}, {0, -1}, {-1, 0}};
        int dirIdx = 0;
        int i = 0;
        int j = 0;
        mat[i][j] = 1;
        auto isValid = [&n](int i, int j) -> bool
        {
            // 判断输入的i,j是否在矩阵范围里面
            return i >= 0 && i < n && j >= 0 && j < n;
        };
        while (1)
        {

            int next_i = i + dirs[dirIdx][0];
            int next_j = j + dirs[dirIdx][1];
            if (!isValid(next_i, next_j) || mat[next_i][next_j] != 0) // 判断当前方向有没有碰壁||已填冲
            {
                // 需要切换方向
                dirIdx = (dirIdx + 1) % 4;
                // 需要判断切换方向之后的下一个位置是否已被填充||超出范围
                // 如果是，那说明Mat已经填充完毕
                next_i = i + dirs[dirIdx][0];
                next_j = j + dirs[dirIdx][1];
                if (!isValid(next_i, next_j) || mat[next_i][next_j] != 0)
                    return mat;
                else
                    mat[next_i][next_j] = mat[i][j] + 1;
            }
            else
            {
                // 不用切换方向
                next_i = i + dirs[dirIdx][0];
                next_j = j + dirs[dirIdx][1];
                mat[next_i][next_j] = mat[i][j] + 1;
            }
            i = next_i;
            j = next_j;
        }
        cout << "???";
        return mat;
    }
};

int main()
{
    Solution so;
    vector<int> test{1, 2, 3, 4, 5};
    auto print_arr = [&](vector<int> &v) -> void
    {
        for (auto num : v)
            cout << num << " ";
    };
    for (auto v : so.generateMatrix(1))
    {
        print_arr(v);
        cout << endl;
    }

    return 0;
}