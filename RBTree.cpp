#include "RBTree.h"


// citation: bst insertion from serene cheon's gatoravl project
RBTree::Node* RBTree::insertHelper(Node* root, City city) {
    if (root == nullptr) { // when root is empty, create new node
        count++;
        return new Node(city);
    }
    if (city.get_temp() < root->city.get_temp()) { // when temperature less than root's temperature
        root->left = insertHelper(root->left, city);
    }
    else if (city.get_temp() > root->city.get_temp()) {// when temperature greater than root's temperature
        root->right = insertHelper(root->right, city);
    }

    balance(root); // balance

    return root;
}

// right rotate
// citation: serene cheon's gatoravl rotation functions, rotate algorithm (https://www.programiz.com/dsa/red-black-tree)
void RBTree::rightRotate(Node* root) {
    Node* child = root->left;
    root->left = child->right;

    if (root->left != nullptr)
        root->left->parent = root;

    child->parent = root->parent;

    if (root->parent == nullptr)
        root_ = child;
    else if (root == root->parent->left)
        root->parent->left = child;
    else
        root->parent->right = child;

    child->right = root;
    root->parent = child;
}

// left rotation
// citation: serene cheon's gatoravl rotation functions, rotate algorithm (https://www.programiz.com/dsa/red-black-tree)
void RBTree::leftRotate(Node* root) {
    Node* child = root->right;
    root->right = child->left;

    if (root->right != nullptr)
        root->right->parent = root;

    child->parent = root->parent; // copy parent

    if (root->parent == nullptr)
        root_ = child;
    else if (root == root->parent->left)
        root->parent->left = child;
    else
        root->parent->right = child;

    child->left = root;
    root->parent = child;
}

void RBTree::balance(Node* root) {
    Node* parent = nullptr;
    Node* grand = nullptr;
    Node* uncle = nullptr;

    while (root != root_ && root->parent != nullptr && root->parent->color == 1) { // parent is red
        parent = root->parent;
        grand = parent->parent;

        // if parent is left child of grandparent
        if (parent == grand->left) {
            uncle = grand->right;
            // 1) uncle is red, recolor
            if (uncle != nullptr && uncle->color == 1) {
                parent->color = 0;
                grand->color = 1;
                uncle->color = 0;
                root = grand;
            } else {
                // 2) node is right child of parent, left rotate
                if (root == parent->right) {
                    //leftRotate(root);
                    leftRotate(parent);
                    root = parent;
                    parent = root->parent;
                }
                // 3) node is left child of parent, right rotate
                //swap(parent->color, grand->color);
                rightRotate(grand);
                parent->color = 0;
                grand->color = 1;
                root = parent;
            }
        }
        else { // if parent is right child of grandparent
            uncle = grand->left;
            // 1) uncle is red, recolor
            if (uncle != nullptr && uncle->color == 1) {
                parent->color = 0;
                grand->color = 1;
                uncle->color = 0;
                root = grand;
            }
            else { // 2) node is left child of parent, right rotate
                if (root == parent->left) {
                    //rightRotate(root);
                    rightRotate(parent);
                    root = parent;
                    parent = root->parent;
                }
                // 3) node is right child of parent, left rotate
                //swap(parent->color, grand->color);
                leftRotate(grand);
                parent->color = 0;
                grand->color = 1;
                root = parent;
            }
            if (root == root_)
                break;
        }
    }
    root_->color = 0; // root is always black
}

// citation: serene cheon's gatoravl
void RBTree::printInorderHelper(Node* root) {
    if (root == nullptr) // when tree is empty
        cout<<endl;
    // inorder traversal
    else{
        printInorderHelper(root->left);
        root->city.print();
        cout<<endl;
        printInorderHelper(root->right);
    }

}

void RBTree::insert(City city) {
    root_ = insertHelper(root_, city);
}

void RBTree::printInorder() {
    printInorderHelper(root_);
}