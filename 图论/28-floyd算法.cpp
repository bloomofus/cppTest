#include <bits/stdc++.h>
using namespace std;
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