#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    string removeDuplicates(string s) {
        string s1{};
        for (auto achar : s) {
            if (s1.empty() == true || s1.back() != achar) s1.push_back(achar);
            else s1.pop_back();
        }
        return s1;
    }
};