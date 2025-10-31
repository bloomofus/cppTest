#include "core.h"
#include "myclass.h"
#include "mytree.h"

using namespace std;
class Solution
{
public:
    TreeNode *buildTree(vector<int> &inorder, vector<int> &postorder)
    {
        deque<int> indeq = vec2deq(inorder);
        deque<int> postdeq = vec2deq(postorder);
        return createTree(indeq, postdeq);
    }

    deque<int> vec2deq(vector<int>& vec){
        deque<int> deq{};
        for(auto node:vec)
            deq.push_back(node);
        return deq;
    }

    TreeNode* createTree(deque<int>& indeq,deque<int>& postdeq){
        if(indeq.empty())
            return nullptr;
        else if (indeq.size() == 1)
        {
            //说明建树快结束了
            TreeNode *lnode = new TreeNode(indeq.front(),nullptr,nullptr);
            return lnode;
        }
        else{
            int mnode_idx = 0;
            while (mnode_idx<indeq.size()&&indeq[mnode_idx]==postdeq[mnode_idx])
                ++mnode_idx;
            mnode_idx = mnode_idx == indeq.size() ? mnode_idx - 1 : mnode_idx;
            TreeNode *mnode = new TreeNode(indeq[mnode_idx], nullptr, nullptr);
            TreeNode *cur = mnode;
            for (int i = mnode_idx - 1; i >= 0; --i)
            {
                cur->left = new TreeNode(indeq[i], nullptr, nullptr);
                cur = cur->left;
            }
            if (mnode_idx==indeq.size())
                return mnode;
            for (int i = 0; i < mnode_idx;++i){
                indeq.pop_front();
                postdeq.pop_front();
            }
            indeq.pop_front();
            mnode->right = createTree(indeq, postdeq);
            return mnode;
        }
    }
};

int main()
{
    Solution so;
    vector<int> nums = {3, 1, 0, 8, 4, 2,9,7 };
    tree t;
    for (auto i : nums)
    {
        t.add(i);
    }
    // t.overshow(t.root);
    TreeNode *rootl = new TreeNode(2,nullptr,nullptr);
    TreeNode *rootr = new TreeNode(3, nullptr, nullptr);
    TreeNode *root = new TreeNode(1,rootl,rootr);

    vector<int> in{1,2};
    vector<int> post{2,1};
    tree myt;
    myt.root = so.buildTree(in, post);
    myt.midshow(myt.root);
    cout << endl;
    myt.postshow(myt.root);
}