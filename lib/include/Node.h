//
// Created by dbusn on 11/2/2023.
//

#ifndef PHOTOMOSAIC_NODE_H
#define PHOTOMOSAIC_NODE_H

#include <algorithm>
#include <iostream>

template <typename K, typename V>
class Node {
public:
    K key;
    V value;
    Node* right;
    Node* left;
    Node* parent;
    int depth;
    Node(K key, V val) : key(key), value(val), right(nullptr), left(nullptr), depth(1), parent(nullptr) { }
    void insertNode(Node<K, V>* toInsert);
    void updateDepth();
    void balance();
    void rightRotate();
    void leftRotate();
    V getValue(K key);
    ~Node();
};

template<typename K, typename V>
V Node<K, V>::getValue(K key) {
    if (this->key == key) {
        return this->value;
    } else {
        if (key >= this->key) {
            if (this->right != nullptr)
                return this->right->getValue(key);
            else
                return this->value;
        }
        else {
            if (this->left != nullptr)
                return this->left->getValue(key);
            else
                return this->value;
        }
    }
}

template<typename K, typename V>
Node<K, V>::~Node() {
    delete this->right;
    delete this->left;
}


template <typename K, typename V>
void Node<K, V>::rightRotate() {
    //std::cout << "doing right rotation";
    Node* newParent = this->left;
    Node* rightTree = newParent != nullptr ? newParent->right : nullptr;

    newParent->right = this;
    this->left = rightTree;

    //update parents
    if (newParent != nullptr) {
        newParent->parent = this->parent;
    }
    if (this->parent != nullptr) {
        if (this->parent->left == this) {
            this->parent->left = newParent;
        } else if (this->parent->right == this) {
            this->parent->right = newParent;
        }
    }
    this->parent = newParent;

    newParent->right->updateDepth();
}

template <typename K, typename V>
void Node<K, V>::leftRotate() {
    //std::cout << "doing left rotation";
    Node* newParent = this->right;
    Node* leftTree = newParent != nullptr ? newParent->left : nullptr;

    newParent->left = this;
    this->right = leftTree;

    //update parents
    if (newParent != nullptr) {
        newParent->parent = this->parent;
    }
    if (this->parent != nullptr) {
        if (this->parent->left == this) {
            this->parent->left = newParent;
        } else if (this->parent->right == this) {
            this->parent->right = newParent;
        }
    }
    this->parent = newParent;

    newParent->left->updateDepth();
}

/**
 * Balance the tree
 *
 * @tparam T type of node
 */
template <typename K, typename V>
void Node<K, V>::balance() {
    int left = this->left != nullptr ? this->left->depth : 0;
    int right = this->right != nullptr ? this->right->depth : 0;
    int bFactor = left - right;

    if (bFactor > 1) {

        if (this->left != nullptr) {
            if (this->left->left != nullptr
                && this->left->left->depth >= (this->left->right != nullptr ? this->left->right->depth : - 1)) {
                this->rightRotate();
            } else {
                this->left->leftRotate();
                this->rightRotate();
            }
        }
    } else if (bFactor < -1) {
        if (this->right != nullptr) {
            if (this->right->right != nullptr
                && this->right->right->depth >= (this->right->left != nullptr ? this->right->left->depth : - 1)) {
                this->leftRotate();
            } else {
                this->right->rightRotate();
                this->leftRotate();
            }
        }
    }
}

/**
 * Update the depth of the node
 *
 * @tparam T
 */
template <typename K, typename V>
void Node<K, V>::updateDepth() {
    int left = this->left != nullptr ? this->left->depth : 0;
    int right = this->right != nullptr ? this->right->depth : 0;
    //std::cout << this->key << " l: " << left << " r: " << right;
    this->depth = std::max(left, right) + 1;
    if (this->parent != nullptr) {
        //std::cout << this->key << " l: " << left << " r: " << right;
        this->parent->updateDepth();
    }
}

/**
 * Insert a node in the AVL
 *
 * @tparam T Type of AVL
 * @param toInsert Pointer of node to insert
 */
template <typename K, typename V>
void Node<K, V>::insertNode(Node<K, V>* toInsert) {

    if (toInsert->key >= this->key) {
        if (this->right == nullptr) {
            toInsert->parent = this;
            this->right = toInsert;
        } else {
            this->right->insertNode(toInsert);
        }
    } else {
        if (this->left == nullptr) {

            toInsert->parent = this;
            this->left = toInsert;
        } else {
            this->left->insertNode(toInsert);
        }
    }
    toInsert->updateDepth();
}


#endif //PHOTOMOSAIC_NODE_H
