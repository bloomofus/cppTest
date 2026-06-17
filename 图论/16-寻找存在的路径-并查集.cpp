#include <bits/stdc++.h>
using namespace std;
int main()
{
    // -- 思路
    // 这里主要看并查集的构建过程即可，思路很简单

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
            // 搜索路径压缩
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