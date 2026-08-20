#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    string reverseWords(string s) {
        // -- 思路
        // 先删除首尾空白，然后整体翻转，然后单个单词翻转
        int slow=0;
        for(int fast=0;fast<s.size();++fast)
        {
            // 快指针负责遍历，慢指针负责被更改的位置
            // 所以慢指针的val 0人在意，我只需要它给我提供位置指引
            // 快指针的值如果是有字符的，那么就往慢指针位置填，然后两个指针都++
            // 快指针如果是空字符，那么就需要判断其前面是不是有一个字符
            // 如果是，那么就往慢指针位置填一个空，用来分割单词
            if(s[fast]!=' ')
            {
                s[slow++]=s[fast];
            }
            else if(fast!=0 && s[fast-1]!=' ')
            {
                s[slow++]=' ';
            }
        }
        // 循环结束之后，slow指向中间字符串的末尾的下一位
        // 也有可能是末尾的下下一位，主要看原来的s是不是以空白字符为结尾
        int endIdx=(s[slow-1]==' '?slow-2:slow-1);
        s.resize(endIdx+1);
        // 翻转字符串
        auto reverseStr=[](string& s,int start_,int end_)->void{
            while(start_<end_)
            {
                s[start_]^=s[end_];
                s[end_]^=s[start_];
                s[start_]^=s[end_];
                ++start_;
                --end_;
            }
        };
        reverseStr(s,0,endIdx);
        // 二次翻转
        vector<int> startIdxV{};
        vector<int> endIdxV{};
        for(int i=0;i<s.size();++i)
        {
            if(i==0||s[i-1]==' ') startIdxV.push_back(i);
            if(i==s.size()-1||s[i+1]==' ') endIdxV.push_back(i);
        }
        for(int i=0;i<startIdxV.size();++i)
        {
            reverseStr(s,startIdxV[i],endIdxV[i]);
        }
        return s;
    }
};


auto main()->int{
    Solution s;
    cout<<s.reverseWords("the sky is blue");
};
