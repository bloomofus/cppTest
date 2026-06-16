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
    // 将到达问题转化为动态规划问题
    
    // -- 输入数据
    int n, m;
    cin >> n >> m;
    vector<vector<vector<int>>> distMat(n+1,vector<vector<int>>(n+1,vector<int>(n+1,INT_MAX))); // 经过下面的循环能够初始化第k=0层
    // 初始化第0层：直接边的权重
    for(int i=1; i<=n; ++i)
        distMat[i][i][0] = 0;  // 自环为0
    for(int i=0;i<m;++i)
    {
        int a,b,c;
        cin>>a>>b>>c;
        distMat[a][b][0] = min(distMat[a][b][0], c);  // 处理重边，取最小
    }

    int q;
    cin>>q;
    struct Plan{ int start,end;};
    vector<Plan> plans{};
    for(int i=0;i<q;++i)
    {
        int a,b;
        cin>>a>>b;
        plans.push_back({a,b});
    }

    // -- floyd算法
    for(int k=1;k<=n;++k)
    {
        for(int i=1;i<=n;++i)
        {
            for(int j=1;j<=n;++j)
            {
                 // 防止溢出
                if(distMat[i][k][k-1] != INT_MAX && distMat[k][j][k-1] != INT_MAX)
                {
                    distMat[i][j][k] = min(
                        distMat[i][j][k-1], // 不经过节点k
                        distMat[i][k][k-1] + distMat[k][j][k-1] // 经过节点k
                    );
                }
                else
                {
                    distMat[i][j][k] = distMat[i][j][k-1];
                }
            }
        }
    }
    auto getAns=[&](Plan& plan)->int{
        int ans=distMat[plan.start][plan.end][n];
        return ans==INT_MAX?-1:ans;
    };
    for(int i=0;i<q;++i)
    {
        auto plan=plans[i];
        cout<<getAns(plan)<<(i==q-1?"":"\n");
    }
    
    return 0;
}