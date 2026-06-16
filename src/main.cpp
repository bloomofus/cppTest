#include <bits/stdc++.h>
using namespace std;

int main()
{
    // -- 思路

    // -- 输入数据
    int n;
    cin>>n;
    struct Point
    { 
        int x,y;
        auto takeAction(Point& action)->Point{
            x+=action.x;
            y+=action.y;
            return {x,y};
        }    
        auto testAction(Point& action)->Point{
            return {x+action.x,y+action.y};
        }
        auto getDist(const Point& target, int choice = 1) const -> float {
            float ans = 0.0f;
        
            // 提前计算差值，避免重复减法，并转为 float 防止整数溢出
            float dx = static_cast<float>(target.x - x);
            float dy = static_cast<float>(target.y - y);

            switch (choice) {
                case 1:
                    // 曼哈顿距离: |dx| + |dy|
                    // 使用 fabs 处理浮点数绝对值，或者直接利用 dx,dy 已转浮点的特性
                    ans = std::fabs(dx) + std::fabs(dy);
                    break;
                case 2:
                    // 欧氏距离: sqrt(dx^2 + dy^2)
                    // 修复：加上 sqrt
                    ans = std::sqrt(dx * dx + dy * dy);
                    break;
                default:
                    // 可选：抛出异常或返回 -1 表示错误
                    break;
            }
            return ans;
        }

        auto operator==(Point& other)->bool{
            return x==other.x&&y==other.y;
        }
        auto operator!=(Point& other)->bool{
            return x!=other.x||y!=other.y;
        }
    };
    struct Plan{Point start,end;};
    vector<Plan> plans{};
    for(int i=0;i<n;++i)
    {
        int a,b,c,d;
        cin>>a>>b>>c>>d;
        plans.push_back({{a,b},{c,d}});
    }

    vector<Point> actions{{1,2},{2,1},{2,-1},{1,-2},{-1,-2},{-2,-1},{-2,1},{-1,2}};


    auto getMinStep=[&](Point& start,Point& end)->int{
        vector<vector<int>> minSteps(1001,vector<int>(1001,999999/2));
        minSteps[start.x][start.y]=0;
        int ansSteps=0;
        Point cur=start;
        while(cur!=end)
        {
            float minCost=999999;
            Point mayPos{0,0};
            for(auto action:actions)
            {
                Point newPos=cur.testAction(action);
                if(newPos.x>=1&&newPos.x<=1000&&newPos.y>=0&&newPos.y<=1000)
                {
                    float newPosCost=minSteps[newPos.x][newPos.y]+newPos.getDist(end,1);
                    if(newPosCost<minCost)
                    {
                        mayPos=newPos;
                    }
                }
            }
            cur=mayPos;
            ++ansSteps;
            minSteps[mayPos.x][mayPos.y]=ansSteps;
        }
        return ansSteps;
    };
    for(int i=0;i<n;++i)
    {
        auto plan=plans[i];
        cout<<getMinStep(plan.start,plan.end)<<(i==n-1?"":"\n");
    }
    return 0;
}