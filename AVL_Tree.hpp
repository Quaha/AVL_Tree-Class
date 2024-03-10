#pragma once

class AVL_Tree {

protected:
    struct Node {

        int key = 0;
        int height = 0;

        Node* left = nullptr;
        Node* right = nullptr;

    };

    Node* head = nullptr;
    unsigned int tree_size = 0;

    void __initNode(Node* current_node, int key);
    bool __isInit(Node* current_node) const;

    void __destroyTree(Node* current_node);

    void __smallLeftRotation(Node* current_node, Node* last_node); // Left left node rotation
    void __smallRightRotation(Node* current_node, Node* last_node); // Right right node rotation

    void __bigLeftRotation(Node* current_node, Node* last_node); // Left right node rotation
    void __bigRightRotation(Node* current_node, Node* last_node); // Right left node rotation

    void __insert(int key, Node* current_node, Node* last_node);

    void __getAllElements(int* result, int& i, Node* current_node) const;

    Node* __find(int key) const;
    Node* __lower_bound(int key) const;

public:

    AVL_Tree();
    AVL_Tree(const AVL_Tree& T) = delete;
    ~AVL_Tree();

    AVL_Tree& operator=(const AVL_Tree& T) = delete;

    bool isExists(int key) const;

    void insert(int key); // Adds an element to the tree, if it is already there, then nothing will happen

    int lower_bound(int key) const; // Returns V >= key or key - 1 if there is no suitable value
    int upper_bound(int key) const; // Returns V > key or key - 1 if there is no suitable value

    unsigned int size() const;
    bool empty() const;

    int* getAllElements(); // Returns an allocated array with all elements in sorted order
};