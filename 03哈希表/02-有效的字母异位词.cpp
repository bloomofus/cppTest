#include <bits/stdc++.h>
using namespace std;

class Solution
{
public:
    bool isAnagram(string s, string t)
    {
        // -- 思路
        // 题目的意思就是t中的所有字母都在s里出现过，并且出现的次数也相等，所以使用hashmap而不是hashset
        // 如果hashmap的key是固定的话，就比如这题是26个字母，那么可以使用数组代替hashmap
        auto way = [&]() -> bool
        {
            vector<int> map(26, 0);
            int len = s.size();
            for (auto achar : s)
            {
                map[achar - 'a']++;
            }
            for (auto achar : t)
            {
                if (map[achar - 'a'] <= 0)
                {
                    // map里面没有该字母
                    return false;
                }
                else
                {
                    // 含有该字母
                    map[achar - 'a']--;
                    len--;
                }
            }
            return len == 0;
        };
        return way();
    }
};

int main()
{
    Solution s;
    cout << s.isAnagram("anagram", "nagaram");
    return 0;
}