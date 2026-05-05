#include "core.h"
#include "utils/myclass.h"
#include "mystruct/mytree.h"

using namespace std;
using namespace mystruct;

class Solution
{
public:
    vector<int> nextGreaterElements(vector<int> &nums)
    {
        // 基本的思路还是经典的单调栈，但是由于是循环数组，所以需要拓展这个数组
        // 就是遍历两次，通过模数来控制对应的idx
        vector<int> res(nums.size(), -1);
        stack<int> s{};
        for (int i = 0; i < nums.size() * 2; ++i)
        {
            int fixedIdx = (i % nums.size());
            while (!s.empty() && nums[s.top()] < nums[fixedIdx])
            {
                if (res[s.top()] == -1) // 这里可以优化一下，其实并不需要额外的判断
                    res[s.top()] = nums[fixedIdx];
                s.pop();
            }
            s.push(fixedIdx);
            // cout <<i<<" "<< res << endl;
        }
        return res;
    }
};
int main()
{
    Solution so;
    string str1 = "aaaaa";
    string str2 = "A";
    vector<int> test{1, 2, 3, 4, 3};
    vector<int> test2{1, 3, 4, 2};
    cout << so.nextGreaterElements(test) << endl;
    return 0;
}