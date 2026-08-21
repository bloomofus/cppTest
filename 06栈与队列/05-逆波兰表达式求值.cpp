#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    int evalRPN(vector<string>& tokens) { //["4","13","5","/","+"]
        // -- 思路
        // 在这里只需要维护一个数字组成的栈
        // 每次遇到运算符的时候就更改栈尾部的数字即可
        vector<int> st{};
        for(auto str:tokens)
        {
            if(str=="+")
            {
                if(st.size()<2) // 说明运算的时候只有一个数，报错
                    return INT_MIN;
                else 
                {
                    int last1=st.back();
                    st.pop_back();
                    int last2=st.back();
                    st.pop_back();
                    st.push_back(last2+last1);
                }
            }else if(str=="-")
            {
                if(st.size()<2) 
                    return INT_MIN;
                else 
                {
                    int last1=st.back();
                    st.pop_back();
                    int last2=st.back();
                    st.pop_back();
                    st.push_back(last2-last1);
                }
            }else if(str=="*")
            {
                if(st.size()<2) 
                    return INT_MIN;
                else 
                {
                    int last1=st.back();
                    st.pop_back();
                    int last2=st.back();
                    st.pop_back();
                    st.push_back(last2*last1);
                }
            }else if(str=="/")
            {
                if(st.size()<2) 
                    return INT_MIN;
                else 
                {
                    int last1=st.back();
                    st.pop_back();
                    int last2=st.back();
                    st.pop_back();
                    st.push_back(last2/last1);
                }
            }else
            {
                // 说明该str是数字
                int cur=std::stoi(str);
                st.push_back(cur);    
            }
        }
        // 确定最终结果
        if(st.size()!=1) return INT_MIN;
        else return st[0];
    }
};