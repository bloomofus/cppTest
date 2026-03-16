#include "core.h"
#include "myclass.h"
#include "mytree.h"

using namespace std;

void printMatrixStyle(const std::vector<std::vector<int>> &vec);
vector<vector<int>> sortIntervals(vector<vector<int>> &intervals);

class Solution
{
public:
    int fib(int n)
    {
        if (n == 0)
            return 0;
        else if (n == 1 || n == 2)
            return 1;
        int arr[2]{1, 1};
        bool left{true};
        int now = 3;
        while (now != n)
        {
            arr[left] = arr[0] + arr[1];
            left = !left;
            ++now;
        }
        return arr[0] + arr[1];
    }
};

int main()
{
    Solution so;
    TreeNode *root = nullptr;
    cout << so.fib(4) << endl;
    // std::cout<< so.reconstructQueue(tmp) << std::endl;
    // printMatrixStyle(input_data);
}