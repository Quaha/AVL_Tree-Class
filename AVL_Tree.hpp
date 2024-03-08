#pragma once

#include "libs.hpp"

#include "AVL_Tree.hpp"


class AVL_Tree {

private:
    struct Node {

        int key = 0;
        bool is_init = false;
        int height = 0;

        Node* parent = nullptr;
        Node* left = nullptr;
        Node* right = nullptr;

    };

    Node* head = nullptr;
    unsigned int tree_size = 0;

    void __destroyTree(Node* current_node);
    bool __find(int key, Node* current_node) const;

    void leftLeftRotation(Node* current_node); // Small left rotation
    void rightRightRotation(Node* current_node); // Small right rotation

    void leftRightRotation(Node* current_node); // Big left rotation
    void rightLeftRotation(Node* current_node); // Big right rotation

    void __insert(int key, Node* current_node);

    void __getAllElements(std::vector<int>& result, Node* current_node) const;

    int __lower_bound(int key, Node* current_node) const;

public:
    AVL_Tree() {
        head = new Node;
    }
    AVL_Tree(const AVL_Tree& T) = delete;
    ~AVL_Tree() {
        __destroyTree(head);
    }
    AVL_Tree& operator=(const AVL_Tree& T) = delete;

    bool find(int key) {
        return __find(key, head);
    }

    void insert(int key) { // Adds an element to the tree, if it is already there, then nothing will happen
        __insert(key, head);
    }

    int lower_bound(int key) { // Returns V >= key or key - 1 if there is no suitable value
        return __lower_bound(key, head);
    }

    int upper_bound(int key) { // Returns V > key or key - 1 if there is no suitable value
        return __lower_bound(key + 1, head);
    }

    unsigned int size() {
        return tree_size;
    }

    bool empty() {
        return tree_size == 0;
    }

    std::vector<int> getAllElements() {
        std::vector<int> result(0);
        __getAllElements(result, head);
        return result;
    }
};
