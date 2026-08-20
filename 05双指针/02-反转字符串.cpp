#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    void reverseString(vector<char>& s) {
        // -- 思路
        // 双指针，通过两侧的指针互换，然后向中间靠拢
        int left=0;
        int right=s.size()-1;
        while(left<right)
        {
            s[left]^=s[right];
            s[right]^=s[left];
            s[left]^=s[right];
            ++left;
            --right;
        }
    }
};