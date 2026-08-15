#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    string reverseWords(string s) {
        // -- 思路
        // 只要不是空白字符隔开的字符串都是一个单词
        // 所以只需要检测多少个空白字符（不是首尾）就能知道有多少个单词，同时也能知道新的字符串的总长度
        // 先把整体的字符串翻转，然后再翻转具体的单词更方便，在翻转单词的时候，可以删除多余的空白字符
        // 在这个过程中，也知道最终的字符串长度，最后再把字符串截断到最终长度即可   

        auto reverse=[](string &s,int start,int end){
            while(start<end){
                swap(s[start],s[end]);
                start++;
                end--;
            }
        };
        reverse(s,0,s.size()-1);
        // 先翻转单词再删除空格，还是先删除空格再翻转单词，还是一边删除空格一边翻转单词
        // 我选择中间逻辑更清晰，也没有多太多的操作
        // 翻转单词
        auto findNextSpace=[](string& s,int start)->int
        {
            // 返回从start开始第一个空格位置
            for(int i=start;i<s.size();++i)
            {
                if(s[i]==' ') return i;
            }
            return  -1; // 返回-1说明没找到
        };
        auto findNextChar=[](string& s,int start)->int
        {
            // 返回从start开始第一个字符位置
            for(int i=start;i<s.size();++i)
            {
                if(s[i]!=' ') return i;
            }
            return  -1; // 返回-1说明没找到
        };


        // 原地删除字符串中多余的空格
        // 删除很容易但是原地删除很麻烦
        // 必要的空格就是两个单词之间的空格，其余的都是多余的空格
        // 从s的每个位置开始遍历，找到下一个单词的开始位置和结束位置，将单词原地转移到当前的遍历位置
        // 之后再将当前遍历位置设置为单词结束的后一个位置
        int cur=0;
        while(cur<s.size())
        {
            int wordStart=findNextChar(s,cur);
            int wordEnd=findNextSpace(s,wordStart)-1;
            if(wordStart!=-1)
            {
                // 如果单词开始的位置是合理的，那么单词结束的位置必然是合理的/或者找不到wordEnd=-2
                if(wordEnd==-2) wordEnd=s.size()-1;
                for(int j=0;j<wordEnd-wordStart+1;++j)
                {
                    // 这个循环会把单词原地向前推
                    swap(s[cur+j],s[wordStart+j]);
                }
                // 这里将单词原地前移到没有空格的位置
                // 这里刚好可以对单词进行翻转
                reverse(s,cur,cur+wordEnd-wordStart);
                cur=cur+wordEnd-wordStart+2; // 刚刚单词结尾的下一个位置的下一个位置（预留一个空格）
            }
            else 
            {
                // 找不到下一个单词了，说明已经到结尾了，开始对字符串resize
                // 当然也有情况是末尾只有一个空格，就直接退出循环这个代码执行不了，所以可以统一是退出循环执行这个代码
                s.resize(cur-1);
            }
        }
        s.resize(cur-1);
        return s;
    }
};


int main()
{
    Solution s;
    string test{" asdasd df f"};
    cout<<s.reverseWords(test);
    return 0;
}