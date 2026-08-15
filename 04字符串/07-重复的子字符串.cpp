#include <bits/stdc++.h>
using namespace std;



class Solution {
public:
    bool repeatedSubstringPattern(string s) {
        // -- 思路
        // 如果父字符串可以由子字符串重复组成，那么父字符串长度一定可以被整数整除
        // 因此遍历整数的同时不断验证其是否由字串重复构成
        // 字串长度越大，判断的压力就越小，因此遍历的整数由大到小
        for(int i=2;i<=s.size();++i)
        {
            // 这里的i是指i个子字符串组合成父字符串
            // 这样遍历比子字符串的大小遍历更简单
            if(isComposedBy(s,i)) return true;
        }
        return false;
    }

    bool isComposedBy(string &s,int subStrNUm)
    {
        if(s.size()%subStrNUm ==0)
        {
            // 说明整除了
            int subStrLen=s.size()/subStrNUm;
            for(int i=1;i<subStrNUm;++i)
            {
                // 整个循环都通过才说明父字符串可以由子字符串重复组成
                // 如果循环不通过直接返回false
                for(int idx=subStrLen*i;idx<subStrLen*(i+1);++idx)
                {
                    if(s[idx]!=s[idx%subStrLen]) return false;
                }
            }
            return true;
        }
        else return false;
    }
};


int main()
{
    Solution s;
    cout<<s.repeatedSubstringPattern("abab");
    return 0;
}