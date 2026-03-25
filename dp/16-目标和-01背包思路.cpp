#include "core.h"
#include "myclass.h"
#include "mytree.h"

using namespace std;


class Solution {
public:
    int findTargetSumWays(vector<int>& nums, int target) {
        //目标和问题可以将整数和负数分为两个集合，两个集合的差是目标target
        //于是问题就变为集合A的总和-集合B的总和=target
        //并且集合A的总和+集合B的总和=nums总和
        //因此可以得出集合A的总和的大小和集合B的总和的大小
        //于是题目就变为从nums里面取出一些数其和为新的target
        //从集合中取特定的物品，这个就是01背包问题
        //dp[i]的含义就是从Nums中取出的数的集合其总和为i的方式数量
        //递归公式就是dp[i]=dp[i]+dp[i-w]，
        //其中右侧的dp[i]就是对于当前的数字w，不取该数字能组成的总和为i的方式数量
        //dp[i-w]表示对于当前数字w，选择该数字加入集合，集合总和为i的可能性数量
        if(nums.size()==1){
            if(nums[0]==target&&nums[0]==-target) return 2;
            else if(nums[0]!=target&& nums[0]!=-target) return 0;
            else return 1;
        }
        int sum=0;
        for(auto num:nums) sum+=num;
        target=(sum-target)/2;
        vector<int> dp(target+1,0);
        dp[0]=1;
        for(auto w:nums){
            for(int j=target-w;j>=0;--j){
                dp[j+w]+=dp[j];
            }
        }
        return dp[target];
    }
};


int main()
{
    Solution so;
    vector<int> test{0,0,1};
    cout << so.findTargetSumWays(test,0)<< endl;
}