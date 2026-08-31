#include <bits/stdc++.h>
#include "tree.h"
using namespace std;

class Solution {
public:
    vector<int> rightSideView(TreeNode* root) {
        // -- 思路：
        // 层序遍历取最后一位
        if(root==nullptr) return {};
        deque<TreeNode*> dq{root};
        vector<int> res{};
        while(dq.size()>0)
        {
            int loop=dq.size();
            for(int i=0;i<loop;++i)
            {
                TreeNode* cur=dq.front();
                dq.pop_front();
                if(cur->left) dq.push_back(cur->left);
                if(cur->right) dq.push_back(cur->right);
                if(i==loop-1) 
                {
                    // 这个就是层序遍历的最后一位
                    res.push_back(cur->val);
                }
            }
        }
        return res;
    }
};