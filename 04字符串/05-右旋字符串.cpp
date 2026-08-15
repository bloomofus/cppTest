#include <bits/stdc++.h>
using namespace std;

auto solution=[]()->string
{
    // -- 思路
    // 假设输入是abcdefg,2，那么就是把f慢慢往前替换，然后g也慢慢往前替换，复杂度是0(mn)
    int n;
    cin>>n;
    string s;
    cin>>s;
    // 如果字符串长度是m，那么就需要把f向前替换m-n次
    int m=s.size();
    for(int cur=m-n;cur<m;++cur)
    {
        // cur是当前需要替换到前面的位置
        for(int i=0;i<m-n;++i)
        {
            swap(s[cur-i-1],s[cur-i]);
        }
    }
    return s;

};

int main()
{
    cout<<solution();
    return 0;
}