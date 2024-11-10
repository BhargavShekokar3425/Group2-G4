#include <bits/stdc++.h>
using namespace std;

template <typename T>
class TreeNode {
public:
    T sum;
    T min;
    T max;
    int count;  // Count of elements in this segment
    TreeNode* left;
    TreeNode* right;

    TreeNode(T val) {
        sum = val;
        min = val;
        max = val;
        count = 1;
        left = right = nullptr;
    }
};

template <typename T>
class SegmentTree {
private:
    TreeNode<T>* root;

    // Utility function to build the segment tree from a vector
    TreeNode<T>* buildTree(const vector<T>& v, int low, int high) {
        if (low == high) {
            return new TreeNode<T>(v[low]);
        }

        int mid = (low + high) / 2;
        TreeNode<T>* node = new TreeNode<T>(0);
        node->left = buildTree(v, low, mid);
        node->right = buildTree(v, mid + 1, high);

        // Update the internal node values based on the children
        node->sum = node->left->sum + node->right->sum;
        node->min = std::min(node->left->min, node->right->min);
        node->max = std::max(node->left->max, node->right->max);
        node->count = node->left->count + node->right->count;
        return node;
    }

public:
    // Default constructor
    SegmentTree() : root(nullptr) {}

    // Constructor that builds the tree from an input vector
    SegmentTree(const vector<T>& v) {
        root = buildTree(v, 0, v.size() - 1);
    }

    // Function to initialize the tree with a vector after creation
    void construct(const vector<T>& v) {
        root = buildTree(v, 0, v.size() - 1);
    }

    // Sample function to display the tree using inorder traversal
    void inorderTraversal(TreeNode<T>* node) const {
        if (!node) return;

        inorderTraversal(node->left);
        cout << node->sum << " ";
        inorderTraversal(node->right);
    }

    void display() const {
        inorderTraversal(root);
        cout << endl;
    }
};
