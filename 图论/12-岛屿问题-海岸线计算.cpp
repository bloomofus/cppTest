#include <bits/stdc++.h>
using namespace std;

int main()
{
    // -- 思路
    // 对每一个陆地节点进行遍历，看其有几个相邻的海洋


    // -- 输入数据
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

    // -- 主循环
    vector<vector<int>> around_mat{{0,1},{1,0},{0,-1},{-1,0}}; 
    int sum_lenth=0;
    for(int i=0;i<n;++i)
    {
        for(int j=0;j<m;++j)
        {
            if(g[i][j]==1)
            {
                //如果该节点是陆地，看其有几个相邻的海洋节点，海岸线就多长
                for(auto diff:around_mat)
                {
                    int i_new=i+diff[0];
                    int j_new=j+diff[1];
                    if(i_new>=0&&i_new<n&&j_new>=0&&j_new<m)
                    {
                        if(g[i_new][j_new]==0)
                            ++sum_lenth;
                    }
                    else // 说明当前陆地节点在边缘上
                        ++sum_lenth;
                }
            }
        }
    }
    cout<<sum_lenth;
    return 0;
}