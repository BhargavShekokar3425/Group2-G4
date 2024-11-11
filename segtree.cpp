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

    T rangeSum(TreeNode<T>* node, int low, int high, int qlow, int qhigh) {
        if (low > qhigh || high < qlow) return 0;  // No overlap
        if (low >= qlow && high <= qhigh) return node->sum;  // Total overlap
        int mid = (low + high) / 2;
        return rangeSum(node->left, low, mid, qlow, qhigh) + rangeSum(node->right, mid + 1, high, qlow, qhigh);
    }

     void updateTree(TreeNode<T>* node, int low, int high, int index, T value) {
        if (low == high) {
            node->sum = value;
            node->min = value;
            node->max = value;
            return;
        }
        int mid = (low + high) / 2;
        if (index <= mid) updateTree(node->left, low, mid, index, value);
        else updateTree(node->right, mid + 1, high, index, value);
        
        node->sum = node->left->sum + node->right->sum;
        node->min = std::min(node->left->min, node->right->min);
        node->max = std::max(node->left->max, node->right->max);
        node->count = node->left->count + node->right->count;
    }

    T rangeMin(TreeNode<T>* node, int low, int high, int qlow, int qhigh) {
        if (low > qhigh || high < qlow) return numeric_limits<T>::max();
        if (low >= qlow && high <= qhigh) return node->min;
        int mid = (low + high) / 2;
        return std::min(rangeMin(node->left, low, mid, qlow, qhigh), rangeMin(node->right, mid + 1, high, qlow, qhigh));
    }

    T rangeMax(TreeNode<T>* node, int low, int high, int qlow, int qhigh) {
        if (low > qhigh || high < qlow) return numeric_limits<T>::lowest();
        if (low >= qlow && high <= qhigh) return node->max;
        int mid = (low + high) / 2;
        return std::max(rangeMax(node->left, low, mid, qlow, qhigh), rangeMax(node->right, mid + 1, high, qlow, qhigh));
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

    T rangeSum(int qlow, int qhigh) {
        return rangeSum(root, 0, root->count - 1, qlow, qhigh);
    }

    void update(int index, T value) {
        updateTree(root, 0, root->count - 1, index, value);
    }

    T rangeMin(int qlow, int qhigh) {
        return rangeMin(root, 0, root->count - 1, qlow, qhigh);
    }

    T rangeMax(int qlow, int qhigh) {
        return rangeMax(root, 0, root->count - 1, qlow, qhigh);
    }

    int rangeCount(int qlow, int qhigh) {
        return (qhigh - qlow + 1);
    }

    double rangeAverage(int qlow, int qhigh) {
        T sum = rangeSum(qlow, qhigh);
        int count = rangeCount(qlow, qhigh);
        return count == 0 ? 0 : static_cast<double>(sum) / count;
    }

    T rangeSumGreaterThan(int qlow, int qhigh, T threshold) {
        T sum = 0;
        for (int i = qlow; i <= qhigh; ++i) {
            T value = rangeSum(i, i);
            if (value > threshold) sum += value;
        }
        return sum;
    } 

    void display() const {
        inorderTraversal(root);
        cout << endl;
    }
};


// int main() {
//     // Initialize a vector with some sample data
//     vector<int> v = {5, 8, 6, 3, 2, 7, 4, 1};

//     // Create a Segment Tree from the vector
//     SegmentTree tree(v);

//     // Display the Segment Tree
//     cout << "Displaying Segment Tree:" << endl;
//     tree.display();

//     // Range sum query
//     int sum = tree.rangeSum(0, 8);
//     cout << "Sum in range [2, 5]: " << sum << endl;

//     // Range min query
//     int minVal = tree.rangeMin(2, 5);
//     cout << "Minimum in range [2, 5]: " << minVal << endl;

//     // Range max query
//     int maxVal = tree.rangeMax(2, 5);
//     cout << "Maximum in range [2, 5]: " << maxVal << endl;

//     // Range average query
//     double avg = tree.rangeAverage(2, 5);
//     cout << "Average in range [2, 5]: " << avg << endl;

//     // Update a value and display updated tree
//     cout << "Updating index 3 to 10." << endl;
//     tree.update(3, 10);
//     tree.display();

//     // Extract and display all leaf nodes
//     cout << "Leaf nodes (individual elements in the range):" << endl;
//     queue<TreeNode*> q;
//     q.push(tree.root);

//     // Traverse the tree to find all leaf nodes
//     while (!q.empty()) {
//         TreeNode* node = q.front();
//         q.pop();

//         // Check if it's a leaf node (no children)
//         if (!node->left && !node->right) {
//             cout << "Leaf Node -> Sum: " << node->sum << ", Min: " << node->min
//                  << ", Max: " << node->max << ", Count: " << node->count << endl;
//         }

//         // Push left and right children to the queue if they exist
//         if (node->left) q.push(node->left);
//         if (node->right) q.push(node->right);
//     }

//     return 0;
// }