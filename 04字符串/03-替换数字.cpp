#include <bits/stdc++.h>
using namespace std;

auto solution=[]()->void
{
    // -- 思路
    // 由于不能申请多余的内存，所以只能在原有的基础山对字符串进行扩容
    // 至于扩容多少就需要找到所有数字的数量
    // 如果从前往后遍历，遍历的时候如果是数字，就需要往后扩展，将数字扩展为number
    // 但是这样明显会把原来的字符给盖住
    // 所以试试从后往前去遍历，这样就不会把之前的元素盖住了
    string s;
    cin>>s;
    int count=0;
    int beforeSize=s.size();
    for(auto achar:s)
    {
        if(achar>='0'&&achar<='9') ++count;
    }
    s.resize(s.size()+5*count);
    // cout<<s;
    int cur=s.size()-1; // 当前需要填充的位置
    for(int i=beforeSize-1;i>=0;--i)
    {
        // 循环只遍历前面有实际字符的部分
        char achar=s[i];
        if(achar>='0'&&achar<='9')
        {
            s[cur--]='r';
            s[cur--]='e';
            s[cur--]='b';
            s[cur--]='m';
            s[cur--]='u';            
            s[cur--]='n';
        }
        else s[cur--]=achar;
    }
    cout<<s;
};


int main()
{
    solution();

    return 0;
}