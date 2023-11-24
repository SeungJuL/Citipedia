#pragma once
#include <iostream>
#include <string>
#include "City.h"
using namespace std;

class RBTree {
private:
    struct Node {

        City city;
        Node* left;
        Node* right;
        Node* parent;
        int color;

        Node() : left(nullptr), right(nullptr), parent(nullptr), color(0) {}

        Node(City city) {
            this->city = city;
            left = nullptr;
            right = nullptr;
            parent = nullptr;
            color = 1; // 0 - black, 1 - red
        }
        ~Node() {
            delete left;
            delete right;
            delete parent;
        }
    };

    Node* root_ = nullptr;

    Node* insertHelper(Node* root, City city);
    void leftRotate(Node* root);
    void rightRotate(Node* root);
    void balance(Node* root);

    void printInorderHelper(Node* root);

public:
    void insert(City city);
    void printInorder();
    int count = 0;
};