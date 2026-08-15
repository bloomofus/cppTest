#include <bits/stdc++.h>
using namespace std;



class Solution {
public:
    int strStr(string haystack, string needle) {
        // -- 思路
        // 经典的kmp算法
        // 需要获取最大前缀数组next,需要使用dp的思想
        // dp[i]的求解可以利用到dp[i-1]
        // 当dp[i-1]==0的时候，说明当前没有可以利用的比较结果，所以只用比较str[i]和str[0]
        // 当dp[i-1]!=0的时候，如果利用这个前后缀进行扩展，如果扩展成功，很好，最大前后缀+1
        // 如果失败了，比如AAAAAAD
        //                BBBBBBC
        // 其中AAAAAA和BBBBBBB是相等的前后缀，后来发现c和d不相等，但是 AAAAAA这个字符串的最长前后缀还是可以利用的
        // 假设AAAAAA的最长前后缀是l，那么BBBBBB的后l个字符可以利用，和AAAAAA的前l个字符相等，再比较str[l]和字符C

        // -- 边界条件
        if (needle.empty()) return 0;
        if (haystack.size() < needle.size()) return -1;

        // -- 获取next数组
        auto getNext=[](string& s)->vector<int> 
        {
            vector<int> next(s.size(),0);
            int k=0; // 记录最新比较的位置
            for(int i=1;i<s.size();++i)
            {
                while(k>0 && s[i]!=s[k])
                {
                    k=next[k-1];
                }
                if(s[i]==s[k])
                {
                    ++k;
                    next[i]=k;
                }
                else next[i]=k;
            }
            return next;
        };
        auto next=getNext(needle);
        int i=0;
        int j=0;
        while(j<needle.size()&& i<haystack.size())
        {
            if(haystack[i]==needle[j])
            {
                ++i;
                ++j;
                if(j==needle.size()) return i-needle.size();
            }
            else
            {
                if(j==0)
                {
                    // 必须把i向前移动了
                    ++i;
                    j=0;
                }
                else
                {
                    // 使用next数组
                    j=next[j-1];
                }
            }
        }
        return -1;
    }
};

int main()
{
    Solution s;
    cout<<s.strStr("leetcode","leeto");
    return 0;
}