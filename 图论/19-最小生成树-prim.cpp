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



    // -- 输入数据 
    int n,m;
    cin>>n>>m;
    vector<vector<int>> g(n+1,vector<int>(n+1,-1));
    for(int i=0;i<m;++i)
    {
        int a,b,c;
        cin>>a>>b>>c;
        g[a][b]=c;
        g[b][a]=c;
    }

    // -- prim方法
    // 先随便找一个点，然后看其相邻的最近节点，然后这两个节点和边看成一个节点，重复这个过程
    // 可以把节点附件的边加入待处理数组
    // 第一个节点附件的待处理数组就是其所在的邻接数组行
    // 第一个节点和第二个节点组合，其待处理数组就是第一个节点所在行和第二个节点所在行之和，并且要删除第一个节点和第二个节点相连的边
    // 只要将其标记为已处理即可
    unordered_set<int> closed_node{1};
    int sum_cost=0;
    while(closed_node.size()!=n)
    {
        int may_edge=INT_MAX;
        int may_node1=0;
        int may_node2=0; 
        for(auto node1:closed_node)
        {
            // 遍历相邻边
            for(int node2=1;node2<=n;++node2)
            {
                int edge=g[node1][node2];
                // 判断是否是节点组之内的边或者没有的边
                if(edge==-1||closed_node.find(node2)!=closed_node.end())
                {
                    // 当前边没有连接或者当前节点已经遍历
                    continue;
                }
                else
                {
                    // 可以遍历比较的相邻边
                    if(edge<may_edge)
                    {
                        may_edge=edge;
                        may_node1=node1;
                        may_node2=node2;
                    }
                }
            }
        }
        closed_node.insert(may_node2);
        sum_cost+=may_edge;
    }
    cout<<sum_cost;

    return 0;
}