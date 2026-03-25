#include "core.h"
#include "myclass.h"
#include "mytree.h"

using namespace std;


class Solution {
public:
    int lastStoneWeightII(vector<int>& stones) {
        //解题思路是将这堆石子分成质量类似的两堆石子
        //那么题目就变成从石头中选出一些石头，使其的质量之和尽可能接近其质量的一半
        //接着剩下的就是另一半
        //还是使用01背包的思路去求解
        int sum=0;
        for(auto w:stones) sum+=w;
        int target=sum/2;
        vector<int> dp(target+1,0);
        for(auto w:stones){
            for(int j=target;j>=w;--j){
                int new_w=dp[j-w]+w;
                if(new_w>dp[j]&&new_w<=target) dp[j]=dp[j-w]+w;
            }
        }
        return sum-2*dp[target];
    }
};
int main()
{
    Solution so;
    vector<int> test{2,7,4,1,8,1};
    cout << so.lastStoneWeightII(test)<< endl;
}