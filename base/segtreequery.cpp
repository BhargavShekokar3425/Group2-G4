#include <iostream>
#include <vector>
#include <queue>
#include <limits>
using namespace std;

struct TreeNode {
    int sum;
    int min;
    int max;
    int count;  // Count of elements in this segment
    TreeNode* left;
    TreeNode* right;

    TreeNode(int val) {
        sum = val;
        min = val;  // Initialize min to the same value
        max = val;  // Initialize max to the same value
        count = 1;  // There's one element
        left = right = nullptr;
    }
};

// Class to handle Segment Tree operations
class SegmentTree {
private:
    TreeNode* root;

    // Utility function to build the segment tree from a vector
    TreeNode* buildTree(const vector<int>& v, int low, int high) {
        if (low == high) {
            return new TreeNode(v[low]);
        }

        int mid = (low + high) / 2;
        TreeNode* node = new TreeNode(0);
        node->left = buildTree(v, low, mid);
        node->right = buildTree(v, mid + 1, high);

        // Update the internal node values based on the children
        node->sum = node->left->sum + node->right->sum;
        node->min = min(node->left->min, node->right->min);
        node->max = max(node->left->max, node->right->max);
        node->count = node->left->count + node->right->count;
        return node;
    }

    // Recursive function to get the sum in a specific range
    int rangeSum(TreeNode* node, int low, int high, int qlow, int qhigh) {
        if (low > qhigh || high < qlow) {
            return 0;  // No overlap
        }
        if (low >= qlow && high <= qhigh) {
            return node->sum;  // Total overlap
        }
        // Partial overlap
        int mid = (low + high) / 2;
        return rangeSum(node->left, low, mid, qlow, qhigh) +
               rangeSum(node->right, mid + 1, high, qlow, qhigh);
    }

    // Utility function to update the segment tree when a value changes
    void updateTree(TreeNode* node, int low, int high, int index, int value) {
        if (low == high) {
            node->sum = value;
            node->min = value;
            node->max = value;
            return;
        }
        int mid = (low + high) / 2;
        if (index <= mid) {
            updateTree(node->left, low, mid, index, value);
        } else {
            updateTree(node->right, mid + 1, high, index, value);
        }
        // Update the parent node
        node->sum = node->left->sum + node->right->sum;
        node->min = min(node->left->min, node->right->min);
        node->max = max(node->left->max, node->right->max);
        node->count = node->left->count + node->right->count;
    }

    // Recursive function to get the min in a specific range
    int rangeMin(TreeNode* node, int low, int high, int qlow, int qhigh) {
        if (low > qhigh || high < qlow) {
            return numeric_limits<int>::max();  // No overlap
        }
        if (low >= qlow && high <= qhigh) {
            return node->min;  // Total overlap
        }
        // Partial overlap
        int mid = (low + high) / 2;
        return min(rangeMin(node->left, low, mid, qlow, qhigh), rangeMin(node->right, mid + 1, high, qlow, qhigh));
    }

    // Recursive function to get the max in a specific range
    int rangeMax(TreeNode* node, int low, int high, int qlow, int qhigh) {
        if (low > qhigh || high < qlow) {
            return numeric_limits<int>::min();  // No overlap
        }
        if (low >= qlow && high <= qhigh) {
            return node->max;  // Total overlap
        }
        // Partial overlap
        int mid = (low + high) / 2;
        return max(rangeMax(node->left, low, mid, qlow, qhigh), rangeMax(node->right, mid + 1, high, qlow, qhigh));
    }

    // Utility function to perform inorder traversal of the tree
void inorderTraversal(TreeNode* node) {
    if (!node) return;

    inorderTraversal(node->left);
    cout << node->sum << " ";
    inorderTraversal(node->right);
}

// Utility function to perform level order traversal of the tree
void levelOrderTraversal(TreeNode* node) {
    if (!node) return;

    queue<TreeNode*> q;
    q.push(node);

    while (!q.empty()) {
        TreeNode* temp = q.front();
        q.pop();
        cout << "Sum: " << temp->sum << ", Min: " << temp->min 
             << ", Max: " << temp->max << ", Count: " << temp->count << endl;

        if (temp->left) q.push(temp->left);
        if (temp->right) q.push(temp->right);
    }
}


public:
    // Constructor to build the tree from the input vector
    SegmentTree(const vector<int>& v) {
        root = buildTree(v, 0, v.size() - 1);
    }

    // Function to display the tree
    void display() {
        cout << "Inorder Traversal of Segment Tree: ";
        inorderTraversal(root);
        cout << endl;
        levelOrderTraversal(root);
        cout << endl;
    }

    // Function to get the sum in the range [qlow, qhigh]
    int rangeSum(int qlow, int qhigh) {
        return rangeSum(root, 0, root->count - 1, qlow, qhigh);
    }

    // Function to update the value at a given index
    void update(int index, int value) {
        updateTree(root, 0, root->count - 1, index, value);
    }

    // Function to get the minimum in the range [qlow, qhigh]
    int rangeMin(int qlow, int qhigh) {
        return rangeMin(root, 0, root->count - 1, qlow, qhigh);
    }

    // Function to get the maximum in the range [qlow, qhigh]
    int rangeMax(int qlow, int qhigh) {
        return rangeMax(root, 0, root->count - 1, qlow, qhigh);
    }

    // Function to get the count of elements in the range [qlow, qhigh]
    int rangeCount(int qlow, int qhigh) {
        return (qhigh - qlow + 1);  // The count is simply the difference in indices
    }

    // Function to calculate the average in the range [qlow, qhigh]
    double rangeAverage(int qlow, int qhigh) {
        int sum = rangeSum(qlow, qhigh);
        int count = rangeCount(qlow, qhigh);
        return count == 0 ? 0 : static_cast<double>(sum) / count;  // Handle division by zero
    }

    // Function to get the sum of salaries greater than a threshold
    int rangeSumGreaterThan(int qlow, int qhigh, int threshold) {
        int sum = 0;
        for (int i = qlow; i <= qhigh; ++i) {
            int salary = rangeSum(i, i);  // Query the individual salary
            if (salary > threshold) {
                sum += salary;
            }
        }
        return sum;
    }
};
