#include "RBTree.h"

// citation: bst insertion from Serene Cheon's project 1
RBTree::Node* RBTree::insertHelper(Node* root, City city) {
    if (root == nullptr) // when root is empty, create new node
        return new Node(city);
    if (city.get_temp() < root->city.get_temp())  // when temperature less than root's temperature
        root->left = insertHelper(root->left, city);
    else if (city.get_temp() > root->city.get_temp())  // when temperature greater than root's temperature
        root->right = insertHelper(root->right, city);

    balance(root); // balance

    return root;
}

// right rotate
// citation: Serene Cheon's project 1 rotation, rotate algorithm (https://www.programiz.com/dsa/red-black-tree)
void RBTree::rightRotate(Node* root) {
    Node* child = root->left;
    root->left = child->right;

    if (root->left != nullptr) // when child is null
        root->left->parent = root;

    child->parent = root->parent; // copy parent

    if (root->parent == nullptr) // when parent is null
        root_ = child;
    else if (root == root->parent->left) // when root is left child of parent
        root->parent->left = child;
    else
        root->parent->right = child;

    // update root and child
    child->right = root;
    root->parent = child;
}

// left rotation
// citation: Serene Cheon's project 1 rotation, rotate algorithm (https://www.programiz.com/dsa/red-black-tree)
void RBTree::leftRotate(Node* root) {
    Node* child = root->right;
    root->right = child->left;

    if (root->right != nullptr) // when child is null
        root->right->parent = root;

    child->parent = root->parent; // copy parent

    if (root->parent == nullptr) // when parent is null
        root_ = child;
    else if (root == root->parent->left) // when root is left child of parent
        root->parent->left = child;
    else
        root->parent->right = child;

    // update root and child
    child->left = root;
    root->parent = child;
}

// balance tree
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
                    leftRotate(parent);
                    root = parent;
                    parent = root->parent;
                }
                // 3) node is left child of parent, right rotate
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
                    rightRotate(parent);
                    root = parent;
                    parent = root->parent;
                }
                // 3) node is right child of parent, left rotate
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

// inorder traversal
// citation: Serene Cheon's project 1 inorder traversal
void RBTree::printInorderHelper(Node* root, string name) {
    if (root == nullptr) // when tree is empty
        cout << "";
    else {
         printInorderHelper(root->left, name);
         if(root->city.get_country() == name){
             root->city.print();
             cout << endl;
         }
         printInorderHelper(root->right, name);
    }
}

// insert city
void RBTree::insert(City city) {
    root_ = insertHelper(root_, city);
}

// print inorder
void RBTree::printInorder(string name) {
    printInorderHelper(root_, name);
}