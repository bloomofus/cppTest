#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    bool isValid(string s) {
        stack<char> st{};
        for(auto achar:s)
        {
            if(st.empty()==true)
            {
                st.push(achar);
                continue;
            }
            else
            {
                if(achar=='{'||achar=='['||achar=='(') 
                {
                    st.push(achar);
                }
                else
                {
                    if((achar==')'&&st.top()=='(')
                    ||(achar==']'&&st.top()=='[')
                    ||(achar=='}'&&st.top()=='{'))
                    {
                        st.pop();
                    }
                    else return false;

                }
            }
        }
        return st.empty();
    }
};