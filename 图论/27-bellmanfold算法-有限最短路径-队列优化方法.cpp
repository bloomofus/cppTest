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
    // 这个是队列优化的方法，一开始的队列里面只有初始节点，通过对初始节点的每个边进行松弛，
    // 就能得到距离初始节点一条边的最短路径可以到达的节点
    // 由于初始节点的下游节点更新了更短的路径，所以需要把其加入处理队列
    // 但是要根据循环轮次依次添加，从而实现获取松弛n次从开始节点的最短路径

    // -- 输入数据
    int n, m;
    cin >> n >> m;
    vector<vector<pair<int, int>>> g(n + 1); // 邻接表：g[u] = {(v, w), ...} 表示从 u 到 v 权重为 w

    for (int i = 0; i < m; ++i)
    {
        int a, b, c;
        cin >> a >> b >> c;
        g[a].push_back({b, c});
        // 如果是无向图，添加反向边（权重也是 c，不是 -c！）
        // g[b].push_back({a, c});
    }
    int src,dst,k;
    cin>>src>>dst>>k;

    // -- bellmanfold算法-有限最短路径
    queue<int> processV{};
    processV.push(src);
    vector<int> dist(n+1,INT_MAX);
    dist[src]=0;

    for(int i=0;i<=k;++i)
    {
        queue<int> tmpNewProcessV{};
        vector<int> tmpDist=dist;
        vector<bool> inQueue(n+1,false); // 这个必须在循环内初始化，因为只对tmpNewProcessV生效

        while(!processV.empty())
        {
            // 遍历这个处理队列
            auto u=processV.front();
            processV.pop();

            // 如果当前节点距离是无穷大，跳过
            // if (dist[u] == INT_MAX) continue; // 由于这里是队列优化的版本，所以一般不会出现这种情况

            for(auto &edge:g[u])
            {
                // 遍历上游节点的每一条边
                int v=edge.first;
                int w=edge.second;
                long long newDist = (long long)dist[u] + w;
                if(newDist<tmpDist[v])
                {
                    // 到v节点有更短的路径，所以需要把v加入处理队列
                    if(!inQueue[v])
                    {
                        tmpNewProcessV.push(v);
                        inQueue[v]=true;
                    }
                    tmpDist[v]=newDist;
                }
            }
        }
        dist=tmpDist;
        processV=tmpNewProcessV;
    }

    cout<<(dist[dst]==INT_MAX?"unreachable":to_string(dist[dst]));
    
    return 0;
}