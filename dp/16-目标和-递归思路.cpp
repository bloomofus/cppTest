#include "core.h"
#include "myclass.h"
#include "mytree.h"

using namespace std;


class Solution {
public:
    int findTargetSumWays(vector<int>& nums, int target) {
        if(nums.size()==1){
            if(nums[0]==target&&nums[0]==-target) return 2;
            else if(nums[0]!=target&&nums[0]!=-target) return 0;
            else return 1;
        }
        return _findTargetSumWays(nums,target,nums.size()-1);

    }

    int _findTargetSumWays(vector<int>& nums, int target,int idx) {
        if(idx==0){
            if(nums[0]==target&&nums[0]==-target) return 2;
            else if(nums[0]!=target&&nums[0]!=-target) return 0;
            else return 1;
        }
        return _findTargetSumWays(nums,target+nums[idx],idx-1)
            +_findTargetSumWays(nums,target-nums[idx],idx-1);
    }
};


int main()
{
    Solution so;
    vector<int> test{0,0,1};
    cout << so.findTargetSumWays(test,0)<< endl;
}