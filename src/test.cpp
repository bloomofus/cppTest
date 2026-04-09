#include <iostream>
#include <string>
#include <vector>

using std::string;
using std::vector;
using namespace std;
class Solution
{
public:
    // 记录每个小写字母在字符串中第一次出现的位置（起始位置），未出现用 -1 表示
    vector<vector<int>> firstAppearances(const string &s)
    {
        vector<vector<int>> result(26, vector<int>{-1,-1}); // 26个小写字母，每个记录 [start_pos]

        for (int i = 0; i < static_cast<int>(s.size()); ++i)
        {
            int charIdx = s[i] - 'a';
            if (result[charIdx][0] == -1&&result[charIdx][1]==-1)
            { // 第一次出现时记录位置
                result[charIdx][0] = i;
                result[charIdx][1] = i;
            }
            else
                result[charIdx][1] = i;
        }

        return result;
    }

    // 可选：打印结果，方便测试
    static void printResult(const string &s, const vector<vector<int>> &res)
    {
        cout << "字符串: \"" << s << "\"\n";
        for (int i = 0; i < 26; ++i)
        {
            char c = 'a' + i;
            int pos = res[i][0];
            if (pos == -1)
            {
                cout << "字母 '" << c << "' (第" << i + 1 << "个): 未出现\n";
            }
            else
            {
                cout << "字母 '" << c << "' (第" << i + 1 << "个): 首次出现位置 = " << pos  <<"最后："<<res[i][1]<<"\n";
            }
        }
        cout << "---\n";
    }
};

int main()
{
    Solution sol;

    // 示例字符串：ababcbacadefegdehijhklij（经典 LeetCode 题目示例）
    string s = "ababcbacadefegdehijhklij";

    vector<vector<int>> result = sol.firstAppearances(s);

    // 打印每个字母的首次出现位置
    Solution::printResult(s, result);

    return 0;
}
