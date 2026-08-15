#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    string reverseStr(string s, int k) {
        // -- 思路
        // 还是和之前一样的思路使用双指针
        // 只不过需要自己去控制一下l、r 的变化转化
        int start=0;
        while(start+2*k-1<s.size())
        {
            // 当满足这个循环要求的时候，就说明当前可以执行一次反转
            int l=start;
            int r=start+k-1;
            while(l<r)
            {
                s[l]^=s[r];
                s[r]^=s[l];
                s[l]^=s[r];
                ++l;
                --r;
            }
            start+=2*k;
        }
        // 处理剩余0~2k个字符
        int l=start;
        int r=start+min(int(s.size())-start,k)-1;
        while(l<r)
        {
            s[l]^=s[r];
            s[r]^=s[l];
            s[l]^=s[r];
            ++l;
            --r;  
        }
        return s;
    }
};

int main()
{
    Solution s;
    cout<<s.reverseStr("abcdefg",2);
    return 0;
}