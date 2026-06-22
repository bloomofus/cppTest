#include <bits/stdc++.h>
using namespace std;

class Solution
{
public:
    bool canConstruct(string ransomNote, string magazine)
    {
        // -- 思路
        // 和字母异位词类似
        vector<int> arr(26, 0);
        for (auto achar : magazine)
        {
            arr[achar - 'a']++;
        }
        for (auto achar : ransomNote)
        {
            if (arr[achar - 'a'] == 0)
                return false;
            arr[achar - 'a']--;
        }
        return true;
    }
};

int main()
{
    return 0;
}