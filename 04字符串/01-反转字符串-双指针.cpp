#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    void reverseString(vector<char>& s) {
        // -- 思路
        // 可以使用双指针，一个指向前边，一个指向后边，然后两个指针同时向中间去遍历
        int l=0;
        int r=s.size()-1;
        while(l<r)
        {
            s[l]^=s[r];
            s[r]^=s[l];
            s[l]^=s[r];
            ++l;
            --r;
        }
    }
};

int main()
{
    return 0;
}