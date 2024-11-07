// SegmentTree.hpp

#ifndef SEGMENTTREE_HPP
#define SEGMENTTREE_HPP

#include <bits/stdc++.h>

using namespace std;

struct TreeNode {
    int sum;
    int min;
    int max;
    int count;  // Count of elements in this segment
    TreeNode* left;
    TreeNode* right;

    TreeNode(int val);
};

class SegmentTree {
private:
    TreeNode* root;

    TreeNode* buildTree(const vector<int>& v, int low, int high);
    int rangeSum(TreeNode* node, int low, int high, int qlow, int qhigh);
    void updateTree(TreeNode* node, int low, int high, int index, int value);
    int rangeMin(TreeNode* node, int low, int high, int qlow, int qhigh);
    int rangeMax(TreeNode* node, int low, int high, int qlow, int qhigh);
    void inorderTraversal(TreeNode* node);
    void levelOrderTraversal(TreeNode* node);

public:
    SegmentTree(const vector<int>& v);
    void display();
    int rangeSum(int qlow, int qhigh);
    void update(int index, int value);
    int rangeMin(int qlow, int qhigh);
    int rangeMax(int qlow, int qhigh);
    int rangeCount(int qlow, int qhigh);
    double rangeAverage(int qlow, int qhigh);
    int rangeSumGreaterThan(int qlow, int qhigh, int threshold);
};

#endif
