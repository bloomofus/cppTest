#pragma once

#include <iostream>

namespace mystruct{
    struct TreeNode
    {
        int val;
        TreeNode *left;
        TreeNode *right;
        TreeNode(int val, TreeNode *ltree, TreeNode *rtree) : val(val), left(ltree), right(rtree) {};
    };

    struct tree
    {
        TreeNode *root;
        TreeNode *insert(TreeNode *&root, int val);
        void add(int val);
        void preshow(TreeNode *root);
        void midshow(TreeNode *root);
        void postshow(TreeNode *root);
        void overshow(TreeNode *root);
        tree() : root(nullptr) {};
    };

    class Node
    {
    public:
        int val;
        Node *left;
        Node *right;
        Node *next;

        Node() : val(0), left(NULL), right(NULL), next(NULL) {}

        Node(int _val) : val(_val), left(NULL), right(NULL), next(NULL) {}

        Node(int _val, Node *_left, Node *_right, Node *_next)
            : val(_val), left(_left), right(_right), next(_next) {}
    };
}
