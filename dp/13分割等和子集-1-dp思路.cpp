#include "core.h"
#include "myclass.h"
#include "mytree.h"

using namespace std;

class Solution
{
public:
    bool canPartition(vector<int> &nums)
    {
        //解题思路：
        //首先题目问你能否将一个vec分割成和相同的两个子vec，那么我将vec求和除以2
        //就可以将题目转化为在vec中找出若干个数其和为target，那么就能将题目简化
        //接着开始遍历数字，目标是target，那么如果历史上我曾经记录了数组总和为target-num
        //那么是不是就可以得出当前数组可以满足题目要求，
        //历史上的记录结果就指向了dp这个思路。
        //
        //dp[I]含义：子数组总和可以构成i
        //dp[i]初始化：全部为false,dp[0]为true
        //遍历顺序：vec顺序遍历，在遍历当前数的时候，需要额外一轮循环，这个循环就是为了更新dp
        //     然后循环从target到Num，去更新这些dp值
        //递推公式:dp[i]=dp[i-num]||dp[i],因为dp[num]肯定为1；
        int sum=0;
        for(auto num:nums){
            sum+=num;
        }
        if(sum%2==1) return false;
        int target=sum/2;
        vector<bool> dp(target+1,false);
        dp[0]=true;
        for(auto num:nums){
            for(int i=target;i>=num;--i){
                dp[i]=dp[i-num]||dp[i];
            }
        }
        return dp[target];
    }
};
int main()
{
    Solution so;
    vector<int> test{1, 5, 11, 5};
    cout << so.canPartition(test)<< endl;
}