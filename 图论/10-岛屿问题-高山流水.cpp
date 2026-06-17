#include <bits/stdc++.h>
using namespace std;

// #define debug

#ifdef debug
    #define dbg cout << "[DEBUG] " << __FILE__ << ":" << __LINE__ << endl;
#else
    #define dbg cout;
#endif

// -- tools
template<typename T>
void print_arr(const vector<T>& arr) {
    cout << "[";
    for (size_t i = 0; i < arr.size(); ++i) {
        if (i > 0) cout << ", "; // 加个逗号更清晰
        cout << arr[i];
    }
    cout << "]" << endl;
}

template<typename T>
void print_mat(const vector<vector<T>>& mat) {
    cout << "[" << endl;
    for (const auto& arr : mat) {
        print_arr(arr);
    }
    cout << "]" << endl;
}


int main()
{
    // -- 思路1：对每一个点的可能流向bfs/dfs
    // 这题和上一题类似，但是体感难很多
    // 上一题通过让dfs搜索能够有一个返回值，在dfs搜索的过程中控制一个索引的所有陆地的共同属性
    // 这题也是类似，通过dfs能够让一个从高点往地点流的水流类似于一个共同索引的陆地，其有一定程度的共同属性
    // 而且该属性需要在dfs搜索的过程中才能知道
    // 比如说有一个流水链3->2->1，那么，如果我先遍历2，我想知道2这个节点是否能够传递到边上
    // 我就看看1这个节点能否传递到边上，如果1可以那么2肯定也可以
    // 那么后遍历3呢，3就要看看2，而便利到3的时候，2的遍历节点已经记录好了，直接取用即可
    // 并且需要两个结构分别记录当前节点是否通向第一组边界和第二组边界，因为可能有这样一个传递链，5->3->1,5->4->2，
    // 前者通向第一组边界，而后者通向第二组边界，这样5通过两条链的信息就可以得知其能够通向两组边界
    // 如果只有一个数据结构记录当前节点是否通向两组边界，那么判断的过程是很麻烦的
    // 事实证明上述思路的做法很麻烦，错是没错的，但是效率太低了，重复判断的情况很常见
    // 思路2:水往高处流
    // 之前的思路是水往低处流，看能否流到边界，这种做法的记忆化存储很麻烦，判断很麻烦容易出错
    // 但是如果直接从边界看水能够从哪些节点流出来，那么这样判断的思路就简单很多，就直接深搜或者广搜然后做好标记就可以
    // 对每一个边界点进行遍历，同时做好closed数组防止重复遍历，从第一组边界可以到达哪些点记录下来
    // 再记录从第二组边界可以到达的点，遍历一下即可得到可以到达两组边界的点



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
    dbg

    // -- dfs搜索变量、函数
    // dfs只需要输入一个节点，然后对其进行dfs将其周围比它大的做好标记
    vector<vector<bool>> firstSet(n,vector<bool>(m,0));
    vector<vector<bool>> secondSet(n,vector<bool>(m,0));
    std::function<void(int,int,bool)> dfs;
    dfs=[&](int i,int j,bool isFirstSet)->void{
        dbg
        vector<vector<bool>>& flagMat=isFirstSet?firstSet:secondSet;
        if(flagMat[i][j]==1)
        {
            // 说明以及访问过了
            return;
        }
        flagMat[i][j]=1; //先对当前节点进行处理
        if(i>=0&&i<n&&j+1>=0&&j+1<m)
        {
            if(g[i][j+1]>=g[i][j]&&flagMat[i][j+1]!=1) dfs(i,j+1,isFirstSet);
        }
        if(i+1>=0&&i+1<n&&j>=0&&j<m)
        {
            if(g[i+1][j]>=g[i][j]&&flagMat[i+1][j]!=1) dfs(i+1,j,isFirstSet);
        }
        if(i>=0&&i<n&&j-1>=0&&j-1<m)
        {
            if(g[i][j-1]>=g[i][j]&&flagMat[i][j-1]!=1) dfs(i,j-1,isFirstSet);
        }
        if(i-1>=0&&i-1<n&&j>=0&&j<m)
        {
            if(g[i-1][j]>=g[i][j]&&flagMat[i-1][j]!=1) dfs(i-1,j,isFirstSet);
        }
    };
    

    // -- 主循环
    for(int i=0;i<n;++i)
        dfs(i,0,true);
    for(int j=0;j<m;++j)
        dfs(0,j,true);
    for(int i=0;i<n;++i)
        dfs(i,m-1,false);
    for(int j=0;j<m;++j)
        dfs(n-1,j,false);

    // print_mat(firstSet);
    // print_mat(secondSet);
    vector<vector<int>> res{};
    for(int i=0;i<n;++i)
    {
        for(int j=0;j<m;++j)
        {
            if(firstSet[i][j]==1&&secondSet[i][j]==1)
                res.push_back({i,j});
        }
    }
    auto print_ans=[&]()->void{
        for(int i=0;i<res.size();++i)
        {
            cout<<res[i][0]<<" "<<res[i][1];
            if(i!=res.size()-1)
                cout<<endl;
        }
    };
    print_ans();
    return 0;
}