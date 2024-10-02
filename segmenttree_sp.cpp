#include <iostream>
#include <vector>
#include <queue>
using namespace std;

// Definition of a tree node for the Segment Tree
struct TreeNode {
    int sum;
    TreeNode* left;
    TreeNode* right;

    TreeNode(int val) {
        sum = val;
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
            // If there's only one element, create a leaf node
            return new TreeNode(v[low]);
        }

        int mid = (low + high) / 2;
        // Create internal nodes and recursively build the left and right subtrees
        TreeNode* node = new TreeNode(0);  // Placeholder value
        node->left = buildTree(v, low, mid);
        node->right = buildTree(v, mid + 1, high);

        // Internal node stores the sum of its children
        node->sum = node->left->sum + node->right->sum;
        return node;
    }

    // Utility function to display the tree (inorder traversal)
    void inorderTraversal(TreeNode* node) {
        if (!node) return;

        inorderTraversal(node->left);
        cout << node->sum << " ";
        inorderTraversal(node->right);
    }

     void levelOrderTraversal(TreeNode* node) {
        if (!node) return;

        queue<TreeNode*> q;
        q.push(node);

        while (!q.empty()) {
            TreeNode* temp = q.front();
            q.pop();
            cout << temp->sum << " ";

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
        cout<<endl;
    }
};

int main() {
    // Input vector
    int n;//No of elements of vector
    cin >> n;
    vector<int> v(n);

    for (int i = 0; i < n; i++) {
        cin >> v[i];
    }

    // Build the segment tree
    SegmentTree st(v);

    // Display the segment tree (inorder traversal)
    st.display();

    return 0;
}
