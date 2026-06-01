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
    // 按照之前的思路把岛屿加上索引，记录岛屿面积与索引的映射


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
    unordered_map<int,int> map{}; // 岛屿索引与面积的索引
    int idx=0;
    vector<vector<int>> flag(n,vector<int>(m,-1));//索引为-1就是海洋，如果是正数则是陆地
    vector<vector<bool>> closed(n,vector<bool>(m,false));
    deque<vector<int>> q{}; // bfs的处理队列
    vector<vector<int>> around_mat{{0,1},{1,0},{0,-1},{-1,0}};
    int size=0; // 记录岛屿的大小
    int max_size=0;

    // -- bfs搜索变量、函数
    auto bfs=[&](int i,int j)->void{
        q.push_back({i,j});
        while(!q.empty())
        {
            // 先将该节点记录索引,再判断是否有新节点加入处理队列
            vector<int> head=q.front();
            i=head[0];
            j=head[1];
            q.pop_front();
            if(closed[i][j]==true)
            {
                continue;
            }
            flag[i][j]=idx;
            closed[i][j]=true;
            ++size;
            for(auto diff:around_mat)
            {
                int i_new=i+diff[0];
                int j_new=j+diff[1];
                if(i_new>=0&&i_new<n&&j_new>=0&&j_new<m&&g[i_new][j_new]==1&&closed[i_new][j_new]==false)
                {
                    //当前节点是陆地，需要加入处理队列
                    q.push_back({i_new,j_new});
                }
            }
        }
        map[idx]=size;
        size=0;     
    };

    // -- 主循环
    for(int i=0;i<n;++i)
    {
        for(int j=0;j<m;++j)
        {
            if(g[i][j]==1&&flag[i][j]==-1)
            {
                size=0;
                ++idx;
                bfs(i,j);//将该节点周围的陆地都加上索引
            }
        }
    }
    auto process_seaNode=[&](int i,int j)->int{
        int sum_size=1;
        unordered_set<int> idxs{}; // 记录海洋周围陆地的索引集合
        for(auto diff:around_mat)
        {
            int i_new=i+diff[0];
            int j_new=j+diff[1];
            if(i_new>=0&&i_new<n&&j_new>=0&&j_new<m&&g[i_new][j_new]==1&&flag[i_new][j_new]!=-1)
            {
                idxs.insert(flag[i_new][j_new]);
            }
        }
        for(auto idx_:idxs) sum_size+=map[idx_];
        return sum_size;
    };
    for(int i=0;i<n;++i)
    {
        for(int j=0;j<m;++j)
        {
            if(g[i][j]==0)
            {
                // 只看海洋节点，然后看其是否连接着陆地，一个节点最多连接四块陆地
                // 还有特殊情况就是没有海洋节点、没有陆地节点
                max_size=max(max_size,process_seaNode(i,j));
            }
        }
    }

    // print_mat(flag);
    // cout<<idx<<endl;
    // for(int i=1;i<=idx;++i)
    //     cout<<"idx: "<<i<<" size: "<<map[i]<<endl;
    auto max3=[](int a,int b,int c)->int{
        return max(max(a,b),c);
    };
    cout<<max3(max_size,map[idx],1); // 第一个是常规情况，第二个是没有海洋节点，第三个是没有陆地节点
    return 0;
}