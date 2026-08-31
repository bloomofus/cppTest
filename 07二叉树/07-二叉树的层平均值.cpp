#include <bits/stdc++.h>
#include "tree.h"
using namespace std;

class Solution {
public:
    vector<double> averageOfLevels(TreeNode* root) {
        // -- 思路：
        // 层序遍历，每层累加所有节点值，最后除以该层节点数得到平均值
        // 比如树 [3,9,20,15,7]，第一层只有3，平均3；第二层9+20=29，平均14.5；第三层15+7=22，平均11
        if(root==nullptr) return {};
        deque<TreeNode*> dq{root};
        vector<double> res{};
        while(dq.size()>0)
        {
            int loop=dq.size();
            double sum=0; // 每层节点值的累加
            for(int i=0;i<loop;++i)
            {
                TreeNode* cur=dq.front();
                dq.pop_front();
                sum+=cur->val;
                if(cur->left) dq.push_back(cur->left);
                if(cur->right) dq.push_back(cur->right);
            }
            // 一层的节点都处理完了，求平均
            res.push_back(sum/loop);
        }
        return res;
    }
};