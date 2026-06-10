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
    // 给我一个邻接数组，我是不知道哪个节点是根节点的，所以第一步应该是找根节点
    // 循环依赖的情况只可能是出现1->2,2->3,3->1这种类似的情况
    // 需要注意，比如1->3,1->2,3->2，意思是2依赖于1和3，故不能使用简单的bfs
    // 难点在于1，如何判断去循环，2，如何处理1->3,1->2,3->2这种情况的正确打印
    // ××××××××
    // 最核心思路：每次只用考虑打印入度为0的节点即可

    // -- 输入数据 
    int n,m;
    cin>>n>>m;
    vector<vector<int>> g(n,vector<int>(n,0));
    for(int i=0;i<m;++i)
    {
        int father_node,child_node;
        cin>>father_node>>child_node;
        g[father_node][child_node]=1;
    }

    vector<bool> closed(n,false);
    vector<int> cout_res{};
    int closed_num=0;
    while(closed_num!=n)
    {
        bool curLoopAllHaveFather=true;
        for(int j=0;j<n;++j)
        {
            // 判断打印的方法
            // 遍历所有节点,找到所有入度为0的节点进行处理
            if(closed[j]==true) continue;
            bool isNoFather=true;
            for(int i=0;i<n;++i)
            {
                if(g[i][j]!=0)
                {
                    // 当前i节点和j节点之间有边，也就是j节点有入度
                    isNoFather=false;
                    break;
                }
            }
            if(isNoFather)
            {
                // 当前j节点没有入度节点
                closed[j]=true;
                for(int k=0;k<n;++k) g[j][k]=0;
                cout_res.push_back(j);
                closed_num++;
                curLoopAllHaveFather=false;
            }
        }
        if(curLoopAllHaveFather)
        {
            // 判断循环的方法
            // 当前遍历所有未访问的节点，其都有父节点，所以有循环依赖
            cout<<-1;
            return 0;
        }
    }
    auto print_res=[&cout_res](){
        for(int i=0;i<cout_res.size();++i)
        {
            cout<<cout_res[i]<<((i==cout_res.size()-1)?"":" ");
        }
    };
    print_res();
   
    return 0;
}