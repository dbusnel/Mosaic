//
// Created by dbusn on 11/2/2023.
//

#ifndef PHOTOMOSAIC_AVLMAP_H
#define PHOTOMOSAIC_AVLMAP_H

#include "../include/Node.h"

template <typename K, typename V>
class AVLMap {
private:
    int height;
public:
    AVLMap<K, V>(Node<K, V>* root) {
        this->root = root;
    }
    AVLMap<K, V>() {
        this->root = nullptr;
    }

    Node<K, V>* root;
    void insertNode(Node<K, V>*);
    void put(K, V);
    V get(K) const;
};

template<typename K, typename V>
V AVLMap<K, V>::get(K key) const {
    return this->root->getValue(key);
}

/**
 * Insert node given address
 * @tparam T Type of tree
 * @param toInsert Address of node to insert
 */
template <typename K, typename V>
void AVLMap<K, V>::insertNode(Node<K, V>* toInsert) {
    if (this->root == nullptr) {
        this->root = toInsert;
    } else {
        this->root->insertNode(toInsert);
    }
}

/**
 * Insert a node by value
 *
 * @tparam T Type of tree
 * @param val value
 */
template <typename K, typename V>
void AVLMap<K, V>::put(K key, V value) {
    Node<K, V>* toAdd = new Node<K, V>(key, value);
    toAdd->depth = 1;
    if (this->root == nullptr) {
        this->root = toAdd;
    } else {
        this->root->insertNode(toAdd);
    }
    this->root->updateDepth();
    this->root->balance();
    if (this->root->parent != nullptr) {
        this->root = this->root->parent;
    }
}

#endif //PHOTOMOSAIC_AVLMAP_H
