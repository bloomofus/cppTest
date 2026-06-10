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
    struct Edge
    {
        int u,v,w;
        bool operator<(const Edge& other) const{
            return w<other.w;
        }
    };
    vector<Edge> edges(m);
    for(int i=0;i<m;++i)
    {
        cin>>edges[i].u>>edges[i].v>>edges[i].w;
    }
    std::sort(edges.begin(),edges.end());

    // -- kruskal方法
    // 把所有边从小到大进行排序，每次挑选最短的边并且要保证不会成环
    // 如果成环就选下一条边
    // 判断成环的话感觉有点麻烦，需要使用并查集
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

        bool join(int x,int y)
        {
            // 并查集的join的作用是，连接x与y，如果x与y之前不是联通的，那么给x和y连一条线
            // 如果之前是联通的，那么需要返回一个false，告知x与y已经有联通了，
            // 如果还给x和y加一条线，那么就会成为一个环
            // 这个也是图结构里面判断是否成环的重要方法
            int x_root=find(x);
            int y_root=find(y);
            if(x_root==y_root) 
            {
                return false;
            }
            else if(x_root!=y_root)
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
                return true;
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
    int sum_cost=0;
    for(auto edge:edges)
    {
        if(uf.join(edge.u,edge.v)==false)
        {
            // 说明u、v两个节点已经有联通了,不能使用该边
            continue;
        }
        else
        {
            // 说明u、v两个节点没联通，我在uv直接加条线
            sum_cost+=edge.w;
        }
    }
    cout<<sum_cost;

    return 0;
}