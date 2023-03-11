//
// Created by yuanr on 3/11/2023.
//

#ifndef LEETSEGTREE_LEETSEGTREE_H
#define LEETSEGTREE_LEETSEGTREE_H

#include <algorithm>

using namespace std;

class LeetSegTree {

    class SegTreeNode{
    public:
        SegTreeNode* left;
        SegTreeNode* right;
        int start, end;
        int val;
        int flag;
        SegTreeNode(int a, int b){
            start = a;
            end = b;
            val = 0;
            flag = 0;
            left = nullptr;
            right = nullptr;
        }
    };

    void init(SegTreeNode* node){
        initHelper(node, node->start, node->end);
    }

    void initHelper(SegTreeNode* node, int a, int b){
        if(a == b){
            node->val = 0;
            return;
        }
        int mid = (a + b) / 2;
        if(node->left != nullptr){
            destroyTree(node->left);
        }
        if(node->right != nullptr){
            destroyTree(node->right);
        }
        node->left = new SegTreeNode(a, mid);
        node->right = new SegTreeNode(mid+1, b);
        init(node->left);
        init(node->right);
        node->val = 0;
    }

    int queryRange(SegTreeNode* node, int a, int b){
        if(b < node->start || a > node->end){
            return 0;
        }
        if(a <= node->start && b >= node->end){
            return node->val;
        }
        pushDown(node);
        return node->val = max(queryRange(node->left, a, b), queryRange(node->right, a, b));
    }

    void updateRange(SegTreeNode* node, int a, int b, int val){
        if(b < node->start || a > node->end){
            return;
        }
        if(a <= node->start && b >= node->end){
            node->val = val;
            node->flag = 1;
            return;
        }
        pushDown(node);
        updateRange(node->left, a, b, val);
        updateRange(node->right, a, b, val);

        node->val = max(node->left->val, node->right->val);
    }

    void pushDown(SegTreeNode* node){
        if(node->flag){
            node->left->val = node->val;
            node->right->val = node->val;
            node->left->flag = 1;
            node->right->flag = 1;
            node->flag = 0;
        }
    }

    void destroyTree(SegTreeNode* node){
        if(node == nullptr){
            return;
        }
        destroyTree(node->left);
        destroyTree(node->right);
        delete node;
    }

    //TESTING

    SegTreeNode* root;

public:
    LeetSegTree(int a, int b){
        root = new SegTreeNode(a, b);
        init(root);
    }

    ~LeetSegTree(){
        destroyTree(root);
    }

    void update(int a, int b, int val){
        updateRange(root, a, b, val);
    }

    int query(int a, int b){
        return queryRange(root, a, b);
    }
};


#endif //LEETSEGTREE_LEETSEGTREE_H
