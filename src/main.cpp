#include "core.h"
#include "utils/myclass.h"
#include "mystruct/mytree.h"

using namespace std;

class Solution
{
public:
    bool wordBreak(string s, vector<string> &wordDict)
    {
        return false;
    }

    vector<int> getStart(string& s,string & target)
    {
        return {};

    }

    vector<int> getStrVec(string& s)
    {
        if(s.size()<1)
            return {};
        vector<int> res(s.size(), 0);
        res[0] = 1;
        for (int i = 1; i < s.size(); ++i){
            if(i==1){
                res[1] = 1;
                continue;
            }
            for (int j = 1; j < i; ++j){
                bool isBreak = false;
                for (int k = 0; k < j; ++k){
                    if(s[k]==s[i-j+k]){}
                    else{
                        res[i] = i-j+1;
                        isBreak = true;
                        break;
                    }
                }
                if(isBreak) break;
                //如ababc，假设当前的i对应第二个b，那么走到这说明，当前第二个b需要比对和第一个b是否一致
                //因为next数组的含义就是字符串在第i个位置上和目标不相同，那么需要移动res[i]
                if(s[i]==s[j]){
                    res[i] = i;
                    break;
                }
                else res[i] = i - 1;
            }
        }
        return res;
    }

    
};

int main()
{
    Solution so;
    string s = "leetcode";
    vector<string> wordDict{"leet", "code"};
    cout << so.wordBreak(s,wordDict) << endl;
    string test = "ababcaabc";
    cout << so.getStrVec(test) << endl;
}