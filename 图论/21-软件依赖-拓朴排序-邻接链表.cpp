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
    // 每次只用考虑打印入度为0的节点即可

    // -- 输入数据 
    int n,m;
    cin>>n>>m;
    vector<int> indegree(n,0);
    vector<vector<int>> neighborList(n,vector<int>{});
    for(int i=0;i<m;++i)
    {
        int a,b;
        cin>>a>>b;
        indegree[b]++;
        neighborList[a].push_back(b);
    }

    vector<int> cout_res{};
    vector<bool> closed(n,false);
    while(cout_res.size()!=n)
    {
        bool allIndegreeNoZero=true;
        for(int i=0;i<n;++i)
        {
            if(indegree[i]==0&&closed[i]==false)
            {
                // 入度为0且没有被遍历
                allIndegreeNoZero=false;
                cout_res.push_back(i);
                closed[i]=true;
                for(auto child_node:neighborList[i])
                {
                    indegree[child_node]--;
                }
            }
        }
        if(allIndegreeNoZero)
        {
            // 循环依赖出错
            cout<<-1;
            return 0;
        }
    }
    auto print_res=[&cout_res](){
        for(int i=0;i<cout_res.size();++i)
            cout<<cout_res[i]<<(i==cout_res.size()-1?"":" ");
    };
    print_res();
   
    return 0;
}