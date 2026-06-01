#include <bits/stdc++.h>
using namespace std;

// #define debug

#ifdef debug
    #define dbg cout << "[DEBUG] " << __FILE__ << ":" << __LINE__ << endl;
#else
    #define dbg cout;
#endif

// -- tools
// 辅助函数：获取整数转换为字符串后的长度
int get_digit_width(int val) {
    string s = to_string(val);
    return s.length();
}

// 模板版本：打印一维数组（支持指定宽度）
template<typename T>
void print_arr(const vector<T>& arr, int width) {
    cout << "[";
    for (size_t i = 0; i < arr.size(); ++i) {
        if (i > 0) cout << ", ";
        // setw(width) 设置最小宽度，right 表示右对齐（数字通常右对齐更整齐）
        cout << setw(width) << arr[i];
    }
    cout << "]";
}

// 模板版本：打印二维数组（矩阵）- 自动计算最大宽度并对齐
template<typename T>
void print_mat(const vector<vector<T>>& mat) {
    if (mat.empty()) {
        cout << "[]" << endl;
        return;
    }

    // 1. 遍历所有元素，找到最大数字的字符串长度
    int max_width = 1;
    for (const auto& row : mat) {
        for (const auto& val : row) {
            int w = get_digit_width(val);
            if (w > max_width) max_width = w;
        }
    }
    
    // 为了美观，可以额外加1个空格 padding
    max_width += 1; 

    cout << "[" << endl;
    for (const auto& row : mat) {
        cout << "  "; // 行首缩进
        print_arr(row, max_width);
        cout << endl;
    }
    cout << "]" << endl;
}

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