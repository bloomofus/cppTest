#include "mytree.h"

TreeNode *tree::insert(TreeNode *&root, int val)
{
    if (!root)
        root = new TreeNode(val, nullptr, nullptr);
    else
    {
        if (root->val > val)
            root->left = insert(root->left, val);
        else
            root->right = insert(root->right, val);
    }
    return root;
}

void tree::add(int val)
{
    insert(root, val);
}

void tree::preshow(TreeNode *root)
{
    if (root)
    {
        std::cout << root->val << " ";
        preshow(root->left);
        preshow(root->right);
    }
}

void tree::midshow(TreeNode *root)
{
    if (root)
    {
        midshow(root->left);
        std::cout << root->val << " ";
        midshow(root->right);
    }
}

void tree::postshow(TreeNode *root)
{
    if (root)
    {
        postshow(root->left);
        postshow(root->right);
        std::cout << root->val << " ";
    }
}

void tree::overshow(TreeNode *root)
{
    if(root){
        std::queue<TreeNode *> q;
        q.push(root);
        while(!q.empty()){
            int size = q.size();
            std::cout << "[ ";
            for (int i = 0; i < size; ++i)
            {
                if(q.front()->left)
                    q.push(q.front()->left);
                if(q.front()->right)
                    q.push(q.front()->right);
                std::cout << q.front()->val << " ";
                q.pop();
            }
            std::cout << "] ";
        }
    }
}
