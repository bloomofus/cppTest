#include <bits/stdc++.h>
using namespace std;
int main()
{
    // -- 思路
    // 在将边的节点加入并查集的时候判断当前两个节点是否都在并查集里面，如果是
    // 那么就是多余的边

    // -- 输入数据 
    int n;
    cin>>n;
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
    for(int i=0;i<n;++i)
    {
        int a,b;
        cin>>a>>b;
        if(uf.inSameSet(a,b))
        {
            cout<<a<<" "<<b;
            return 0;
        }
        uf.join(a,b);
    }

    // -- 主循环
    cout<<"  no find ";
   
    return 0;
}