#include "AVL_Tree.hpp"

unsigned int max(unsigned int A, unsigned int B) {
    if (A < B) {
        return B;
    }
    return A;
}

int abs(int V) {
    if (V < 0) {
        return -V;
    }
    return V;
}

void AVL_Tree::__initNode(Node* current_node, int key) {
    tree_size++;

    current_node->key = key;
    current_node->height = 1;

    current_node->left = new Node;
    current_node->right = new Node;
}

bool AVL_Tree::__isInit(Node* current_node) const {
    return (current_node->left != nullptr) && (current_node->right != nullptr);
}

void AVL_Tree::__destroyTree(Node* current_node) {
    if (__isInit(current_node)) {
        __destroyTree(current_node->left);
        __destroyTree(current_node->right);
    }
    delete current_node;
}

void AVL_Tree::__smallLeftRotation(Node* current_node, Node* last_node) {
    Node* left_node = current_node->left;

    if (last_node != nullptr) {
        if (last_node->left == current_node) {
            last_node->left = left_node;
        }
        else {
            last_node->right = left_node;
        }
    }
    else {
        head = left_node;
    }

    current_node->left = left_node->right;
    left_node->right = current_node;

    current_node->height = max(current_node->left->height, current_node->right->height) + 1;
    left_node->height = max(left_node->left->height, left_node->right->height) + 1;
}

void AVL_Tree::__smallRightRotation(Node* current_node, Node* last_node) {
    Node* right_node = current_node->right;

    if (last_node != nullptr) {
        if (last_node->left == current_node) {
            last_node->left = right_node;
        }
        else {
            last_node->right = right_node;
        }
    }
    else {
        head = right_node;
    }

    current_node->right = right_node->left;
    right_node->left = current_node;

    current_node->height = max(current_node->left->height, current_node->right->height) + 1;
    right_node->height = max(right_node->left->height, right_node->right->height) + 1;
}

void AVL_Tree::__bigLeftRotation(Node* current_node, Node* last_node) {
    __smallRightRotation(current_node->left, current_node);
    __smallLeftRotation(current_node, last_node);
}

void AVL_Tree::__bigRightRotation(Node* current_node, Node* last_node) {
    __smallLeftRotation(current_node->right, current_node);
    __smallRightRotation(current_node, last_node);
}

void AVL_Tree::__insert(int key, Node* current_node, Node* last_node) {
    if (!__isInit(current_node)) {
        __initNode(current_node, key);
        return;
    }
    if (key < current_node->key) {
        __insert(key, current_node->left, current_node);
    }
    if (key > current_node->key) {
        __insert(key, current_node->right, current_node);
    }

    int Hl = current_node->left->height;
    int Hr = current_node->right->height;

    if (abs(Hl - Hr) == 0) {
        return;
    }
    if (abs(Hl - Hr) == 1) {
        current_node->height++;
        return;
    }

    if (Hl > Hr) {
        int Hll = current_node->left->left->height;
        int Hlr = current_node->left->right->height;
        if (Hll > Hlr) {
            __smallLeftRotation(current_node, last_node);
        }
        else {
            __bigLeftRotation(current_node, last_node);
        }
    }
    else {
        int Hrl = current_node->right->left->height;
        int Hrr = current_node->right->right->height;
        if (Hrl > Hrr) {
            __bigRightRotation(current_node, last_node);
        }
        else {
            __smallRightRotation(current_node, last_node);
        }
    }
}

void AVL_Tree::__getAllElements(int* result, int& i, Node* current_node) const {
    if (!__isInit(current_node)) {
        return;
    }

    __getAllElements(result, i, current_node->left);
    result[i++] = current_node->key;
    __getAllElements(result, i, current_node->right);
}

AVL_Tree::Node* AVL_Tree::__find(int key) const {
    Node* current_node = head;
    while (__isInit(current_node) && current_node->key != key) {
        if (key < current_node->key) {
            current_node = current_node->left;
        }
        else if (key > current_node->key) {
            current_node = current_node->right;
        }
    }
    return current_node;
}

AVL_Tree::Node* AVL_Tree::__lower_bound(int key) const {
    Node* result = nullptr;
    Node* current_node = head;
    while (__isInit(current_node)) {
        if (current_node->key < key) {
            current_node = current_node->right;
        }
        else {
            result = current_node;
            current_node = current_node->left;
        }
    }
    return result;
}

AVL_Tree::AVL_Tree() {
    head = new Node;
}

AVL_Tree::~AVL_Tree() {
    __destroyTree(head);
}

bool AVL_Tree::isExists(int key) const {
    return __isInit(__find(key));
}

void AVL_Tree::insert(int key) {
    __insert(key, head, nullptr);
}

int AVL_Tree::lower_bound(int key) const {
    Node* result = __lower_bound(key);
    if (result == nullptr) return key - 1;
    return result->key;
}

int AVL_Tree::upper_bound(int key) const {
    Node* result = __lower_bound(key + 1);
    if (result == nullptr) return key - 1;
    return result->key;
}

unsigned int AVL_Tree::size() const {
    return tree_size;
}

bool AVL_Tree::empty() const {
    return tree_size == 0;
}

int* AVL_Tree::getAllElements() {
    int* result = new int[tree_size];
    int i = 0;
    __getAllElements(result, i, head);
    return result;
}