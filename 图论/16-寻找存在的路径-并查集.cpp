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
    struct UnionFind
    {
        vector<int> father{};
        vector<int> rank{};
        UnionFind(int node_num):father(vector<int>(node_num+1,-1)),rank(vector<int>(node_num+1,1))
        {
            for(int i=0;i<=node_num;++i) 
                father[i]=i;
        }

        int find(int x)
        {
            if(father[x]!=x) 
                father[x]=find(father[x]);
            return father[x];
        }

        void join(int x,int y)
        {
            int x_root=find(x);
            int y_root=find(y);
            if(x_root!=y_root)
            {
                if(rank[x_root]==rank[y_root])
                {
                    // 将y的集合加入x
                    father[y_root]=x_root;
                    rank[x_root]++;
                }
                else if(rank[x_root]>rank[y_root])
                {
                    father[y_root]=x_root;
                }
                else
                {
                    father[x_root]=y_root;
                }
            }
        }

        bool inSameSet(int x,int y)
        {
            int x_root=find(x);
            int y_root=find(y);
            return x_root==y_root;
        }
    };
    UnionFind uf(n);
    for(int i=0;i<m;++i)
    {
        int a,b;
        cin>>a>>b;
        uf.join(a,b);
    }
    int source,target;
    cin>>source>>target;

    // -- 主循环
    cout<<uf.inSameSet(source,target);
   
    return 0;
}