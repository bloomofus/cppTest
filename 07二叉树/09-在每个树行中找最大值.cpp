#include <bits/stdc++.h>
#include "tree.h"
using namespace std;

class Solution {
public:
    vector<int> largestValues(TreeNode* root) {
        // -- 思路：
        // 层序遍历，每层记录最大值，遍历完一层就把最大值加入结果
        // 比如树 [1,3,2,5,3,null,9]，第一层最大1；第二层max(3,2)=3；第三层max(5,3,9)=9
        if(root==nullptr) return {};
        deque<TreeNode*> dq{root};
        vector<int> res{};
        while(dq.size()>0)
        {
            int loop=dq.size();
            int maxVal=INT_MIN; // 每层开始前，初始化为最小整数
            for(int i=0;i<loop;++i)
            {
                TreeNode* cur=dq.front();
                dq.pop_front();
                maxVal=max(maxVal, cur->val);
                if(cur->left) dq.push_back(cur->left);
                if(cur->right) dq.push_back(cur->right);
            }
            // 一层的节点都处理完了，当前maxVal就是这层的最大值
            res.push_back(maxVal);
        }
        return res;
    }
};
