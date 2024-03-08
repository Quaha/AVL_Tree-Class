#include "libs.hpp"

#include "AVL_Tree.hpp"

void AVL_Tree::__destroyTree(Node* current_node) {
    if (current_node->is_init) {
        __destroyTree(current_node->left);
        __destroyTree(current_node->right);
    }
    delete current_node;
}

bool AVL_Tree::__find(int key, Node* current_node) const {
    if (!current_node->is_init) {
        return false;
    }
    if (key == current_node->key) {
        return true;
    }
    if (key < current_node->key) {
        return __find(key, current_node->left);
    }
    if (key > current_node->key) {
        return __find(key, current_node->right);
    }
}

void AVL_Tree::leftLeftRotation(Node* current_node) {
    Node* left_node = current_node->left;

    if (current_node->parent != nullptr) {
        if (current_node->parent->left == current_node) {
            current_node->parent->left = left_node;
        }
        else {
            current_node->parent->right = left_node;
        }
    }
    else {
        head = left_node;
    }

    left_node->parent = current_node->parent;
    current_node->parent = left_node;

    left_node->right->parent = current_node;
    current_node->left = left_node->right;
    left_node->right = current_node;

    current_node->height = std::max(current_node->left->height, current_node->right->height) + 1;
    left_node->height = std::max(left_node->left->height, left_node->right->height) + 1;
}

void AVL_Tree::rightRightRotation(Node* current_node) {
    Node* right_node = current_node->right;

    if (current_node->parent != nullptr) {
        if (current_node->parent->left == current_node) {
            current_node->parent->left = right_node;
        }
        else {
            current_node->parent->right = right_node;
        }
    }
    else {
        head = right_node;
    }

    right_node->parent = current_node->parent;
    current_node->parent = right_node;

    right_node->left->parent = current_node;
    current_node->right = right_node->left;
    right_node->left = current_node;

    current_node->height = std::max(current_node->left->height, current_node->right->height) + 1;
    right_node->height = std::max(right_node->left->height, right_node->right->height) + 1;
}

void AVL_Tree::leftRightRotation(Node* current_node) {
    rightRightRotation(current_node->left);
    leftLeftRotation(current_node);
}

void AVL_Tree::rightLeftRotation(Node* current_node) {
    leftLeftRotation(current_node->right);
    rightRightRotation(current_node);
}

void AVL_Tree::__insert(int key, Node* current_node) {
    if (!current_node->is_init) {
        tree_size++;

        current_node->key = key;
        current_node->is_init = true;
        current_node->height = 1;

        current_node->left = new Node;
        current_node->left->parent = current_node;

        current_node->right = new Node;
        current_node->right->parent = current_node;

        return;
    }
    if (key < current_node->key) {
        __insert(key, current_node->left);
    }
    if (key > current_node->key) {
        __insert(key, current_node->right);
    }

    int Hl = current_node->left->height;
    int Hr = current_node->right->height;

    if (std::abs(Hl - Hr) == 0) {
        return;
    }
    if (std::abs(Hl - Hr) == 1) {
        current_node->height++;
        return;
    }

    if (Hl > Hr) {
        int Hll = current_node->left->left->height;
        int Hlr = current_node->left->right->height;
        if (Hll > Hlr) {
            leftLeftRotation(current_node);
        }
        else {
            leftRightRotation(current_node);
        }
    }
    else {
        int Hrl = current_node->right->left->height;
        int Hrr = current_node->right->right->height;
        if (Hrl > Hrr) {
            rightLeftRotation(current_node);
        }
        else {
            rightRightRotation(current_node);
        }
    }
}

void AVL_Tree::__getAllElements(std::vector<int>& result, Node* current_node) const {
    if (!current_node->is_init) return;
    __getAllElements(result, current_node->left);
    result.push_back(current_node->key);
    __getAllElements(result, current_node->right);
}

int AVL_Tree::__lower_bound(int key, Node* current_node) const {
    if (!current_node->is_init) {
        return key - 1;
    }
    if (current_node->key < key) {
        return __lower_bound(key, current_node->right);
    }
    return std::max(current_node->key, __lower_bound(key, current_node->left));
}