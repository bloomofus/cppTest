#include <bits/stdc++.h>
#include "tree.h"
using namespace std;

class Solution {
public:
    vector<vector<int>> levelOrder(Node* root) {
        // -- 思路
        // 和二叉树不是一样的吗
        if(root==nullptr) return {};
        queue<Node*> q{};
        q.push(root);
        vector<vector<int>> res{};
        while(!q.empty())
        {
            int loop=q.size();
            vector<int> curLevel;
            curLevel.reserve(loop);
            for(int i=0;i<loop;++i)
            {
                auto cur=q.front();
                q.pop();
                curLevel.push_back(cur->val);
                for(auto& child : cur->children) q.push(child);
            }
            res.push_back(curLevel);
        }
        return res;
    }
};