#include "core.h"
#include "utils/myclass.h"
#include "mystruct/mytree.h"

using namespace std;
using namespace mystruct;

class Solution
{
public:
    vector<int> nextGreaterElement(vector<int> &nums1, vector<int> &nums2)
    {
        // 和传统的单调栈没有明显的区别，只不过使用map代替原来的vector，记录的是val而非vector记录的idx
        std::unordered_map<int, int> map{};
        std::stack<int> s{};
        for (int i = 0; i < nums2.size(); ++i)
        {
            while (!s.empty() && nums2[s.top()] < nums2[i])
            {
                map[nums2[s.top()]] = nums2[i];
                s.pop();
            }
            s.push(i);
        }
        vector<int> res(nums1.size(), 0);
        for (int i = 0; i < nums1.size(); ++i)
        {
            auto it = map.find(nums1[i]);
            if (it != map.end())
            {
                res[i] = map[nums1[i]];
            }
            else
                res[i] = -1;
        }
        return res;
    }
};
int main()
{
    Solution so;
    string str1 = "aaaaa";
    string str2 = "A";
    vector<int> test{4, 1, 2};
    vector<int> test2{1, 3, 4, 2};
    cout << so.nextGreaterElement(test, test2) << endl;
    return 0;
}