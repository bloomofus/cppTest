#include <bits/stdc++.h>
using namespace std;

auto solution=[](string& s)->string{
    // -- 思路
    // 先从前往后遍历一遍找到所有的数字的个数
    // 根据这个数字个数扩充字符串
    // 最后再从后往前填充字符串
    string templateStr("number");
    int numCount=0;
    for(int i=0;i<s.size();++i)
    {
        if(int('0')<=int(s[i])&&int(s[i])<=int('9'))
        {
            // 当前字符是数字
            ++numCount;
        }
    }
    string newStr(s.size()+5*numCount,' ');
    int sIdx=s.size()-1;
    int newStrIdx=newStr.size()-1;
    for(;sIdx>=0;--sIdx)
    {
        if(int('0')<=int(s[sIdx])&&int(s[sIdx])<=int('9'))
        {
            // 当前字符是数字,需要填充number
            for(int i=templateStr.size()-1;i>=0;--i)
            {
                newStr[newStrIdx--]=templateStr[i];
            }
        }
        else
        {
            // 当前字符不是数字
            newStr[newStrIdx--]=s[sIdx];
        }
    }
    return newStr;
};

auto main()->int{
    string s;
    cin>>s;
    cout<<solution(s);
};