#include "core.h"
#include "myclass.h"
#include "mytree.h"

using namespace std;

class Solution
{
public:
    bool wordBreak(string s, vector<string> &wordDict)
    {
    }
};

int main()
{
    Solution so;
    string s = "leetcode";
    vector<string> wordDict{"leet", "code"};
    cout << so.wordBreak(s,wordDict) << endl;
}