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
    // 所有可能的情况就是，1，没有入度为2或者出度为2的节点，那么这个图就是一个环，删掉最新的边即可
    // 2，有一个节点入度或出度为2，那么这个节点有2个关键边
    // 看这两个关键边是否组成环，如果是那么删除这个关键边，如果都不构成环
    // 那么删除较晚添加的那个关键边


    // -- 输入数据 
    int n;
    cin>>n;
    struct findClass
    {
        int node_num{0};
        vector<vector<int>> fatherV{};
        vector<vector<int>> childV{};
        findClass(int node_num_in):fatherV(vector<vector<int>>(node_num_in+1,vector<int>{})),
                                   childV(vector<vector<int>>(node_num_in+1,vector<int>{})),
                                   node_num(node_num_in) {};

        auto addEdge(int father,int child)->void
        {
           fatherV[child].push_back(father);
           childV[father].push_back(child);
        }

        auto  findTwoFatherNode()->int
        {
            for(int i=1;i<=node_num;++i)
            {
                if(fatherV[i].size()==2) return i;
            }
            return 0; // 没找到入度为2的节点
        }

        auto findTwoChildNode()->int
        {
            for(int i=1;i<=node_num;++i)
            {
                if(childV[i].size()==2) return i;
            }
            return 0;
        }

        auto isLoop(int father,int child)-> bool
        {
            //这个是入度为2的情况
            // 从child到father再到更高的father
            // 由于这里child一般是有两个父节点的节点，而且从child节点开始，所以不用考虑其余节点会有多个父节点
            int cur_node=child;
            int cur_father=father;
            while(fatherV[cur_father].size()>0)
            {
                // 这个循环的终止条件是走到这个线段组合的尽头，也可能是走入循环又回到起点附近
                // 所以需要额外判断
                if(cur_father==child)
                {
                    // 说明cur_father又走到了起始点的child，说明以father节点和child节点为边是个环
                    return true;
                }
                cur_node=cur_father;
                cur_father=fatherV[cur_father][0];
            }
            return false;
        }

        auto isLoop2(int father,int child)-> bool
        {
            //这个是出度为2的情况
            // 从father到child再到更低的child
            // 由于这里father一般是有两个子节点的节点，而且从father节点开始，所以不用考虑其余节点会有多个子节点
            int cur_node=father;
            int cur_child=child;
            while(childV[cur_child].size()>0)
            {
                // 这个循环的终止条件是走到这个线段组合的尽头，也可能是走入循环又回到起点附近
                // 所以需要额外判断
                if(cur_child==father)
                {
                    // 说明cur_child又走到了起始点的father，说明以child节点和father节点为边是个环
                    return true;
                }
                cur_node=cur_child;
                cur_child=childV[cur_child][0];
            }
            return false;
        }

    };
    findClass uf(n);
    int a,b;
    std::map<pair<int,int>,int> map{};
    for(int i=1;i<=n;++i)
    {
        cin>>a>>b;
        map[{a,b}]=i;
        uf.addEdge(a,b);
    }

    int keyNode1=uf.findTwoFatherNode();
    int keyNode2=uf.findTwoChildNode();
    if(keyNode1+keyNode2==0)
    {
        // 没找到入度或出度为2的节点
        // 那么就删除最新加入的那个边
        cout<<a<<" "<<b;
        return 0;
    }
    else if(keyNode1)
    {
        // 入度为2
        int father1=uf.fatherV[keyNode1][0];
        int father2=uf.fatherV[keyNode1][1];
        bool isLoop1=uf.isLoop(father1,keyNode1);
        bool isLoop2=uf.isLoop(father2,keyNode1);
        if(isLoop1)
        {
            // 删除这个边
            cout<<father1<<" "<<keyNode1;
            return 0;
        }
        else if(isLoop2)
        {
            cout<<father2<<" "<<keyNode1;
            return 0;
        }
        else 
        {
            // 两个边都不是loop，删掉最后加入的那个边
            int idx1=map[{father1,keyNode1}];
            int idx2=map[{father2,keyNode1}];
            if(idx1>idx2) cout<<father1<<" "<<keyNode1;
            else cout<<father2<<" "<<keyNode1;
        }
        return 0;
    }
    else if(keyNode2)
    {
        // 出度为2
        int child1=uf.childV[keyNode2][0];
        int child2=uf.childV[keyNode2][1];
        bool isLoop1=uf.isLoop2(keyNode2,child1);
        bool isLoop2=uf.isLoop2(keyNode2,child2);
        if(isLoop1)
        {
            // 删除这个边
            cout<<keyNode2<<" "<<child1;
            return 0;
        }
        else if(isLoop2)
        {
            cout<<keyNode2<<" "<<child2;
            return 0;
        }
        else 
        {
            // 两个边都不是loop，删掉最后加入的那个边
            int idx1=map[{keyNode2,child1}];
            int idx2=map[{keyNode2,child2}];
            if(idx1>idx2) cout<<keyNode2<<" "<<child1;
            else cout<<keyNode2<<" "<<child2;
        }
        return 0;
    }

   
    return 0;
}