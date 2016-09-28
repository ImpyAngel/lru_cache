//
// Created by Impy on 26.09.2016.
//
#include "lru_cache.h"
#include <iostream>

    lru_cache::lru_cache(size_t capacity) {
        root = new node;
        root-> next = root;
        root-> prev = root;
        root-> parent = nullptr;
        root -> right = nullptr;
        root -> left = nullptr;
        size = 0;
        this -> capacity = capacity;
    }

   lru_cache::~lru_cache() {
        del(root);
    }
    void lru_cache::del(lru_cache::node* v) {
        if (v->left != nullptr) del(v->left);
        if (v->right != nullptr) del(v->right);
        delete(v);
    }

    lru_cache::iterator lru_cache::find(key_type key) {
        if (size == 0) return  iterator(root); else {
            node* temp = root -> left;
            while (temp != nullptr && temp->key != key) {
                if (temp->key > key) {
                    temp = temp->left;
                } else {
                    temp = temp->right;
                }
            }
            if (temp == nullptr) temp = root;
            return  iterator(temp);
        }
    }

    std::pair<lru_cache::iterator, bool> lru_cache::insert(value_type x) {
        if (find(x.first).data == end().data) {
            node* noda = (size < capacity) ? new node() :
                                              erase_without_delete(root->next);
            node * temp = root;
            while (temp != nullptr) {
                if (temp == root || temp->key > x.first) {
                    if (temp->left == nullptr) {
                        temp -> left = noda;
                        break;
                    } else {
                        temp = temp->left;
                    }
                } else {
                    if (temp->right == nullptr) {
                        temp -> right = noda;
                        break;
                    } else {
                        temp = temp->right;
                    }
                }
            }
            size++;
            noda -> parent = temp;
            noda ->left = nullptr;
            noda ->right = nullptr;
            noda->key = x.first;
            noda->mapped = x.second;
            noda->prev = root->prev;
            noda->next = root;
            root->prev = noda;
            noda->prev->next = noda;
            return std::make_pair( iterator(noda), true);
        } else {
            return std::make_pair(find(x.first), false);
        }
    }

    lru_cache::node* lru_cache::erase_without_delete(lru_cache::node* v) {
        size--;
        v->next->prev = v->prev;
        v->prev->next = v->next;
        node ** father;
        if (v->parent == root || v->key < v->parent->key)
            father = &v->parent->left; else
            father = &v->parent->right;
        if (v->left == nullptr) {
            *father = v->right;
            if (v->right != nullptr) {
                v->right->parent = v->parent;
            }
        } else {
            if (v->right == nullptr) {
                *father = v->left;
                v->left->parent = v->parent;
            } else {
                node* temp = v->right;
                while (temp->left != nullptr) temp = temp->left;
                if (temp->parent->left == temp) {
                    temp->parent->left = temp->right;
                } else {
                    temp->parent->right = temp->right;
                }
                if (temp->right != nullptr) {
                    temp->right->parent = temp->parent;
                }
                *father = temp;
                temp->left = v->left;
                temp->right = v->right;
                temp->parent = v->parent;
                v->left->parent = temp;
            }
        }
        return (v);
    }
    void lru_cache::erase(lru_cache::iterator v) {
        delete(erase_without_delete(v.data));
    }

    lru_cache::iterator lru_cache::begin() const {
        node* temp = root;
        while(temp ->left != nullptr) {
            temp = temp -> left;
        }
        return iterator(temp);
    }
    lru_cache::iterator lru_cache::end() const {
        return iterator(root);
    }
int main() {
    lru_cache data(5);

    std::cout << '\n';
       std::cout << (data.insert(std::make_pair(1, 1)).second);
       std::cout << (data.insert(std::make_pair(0, 0)).second);
       std::cout << (data.insert(std::make_pair(6, 6)).second);
    for (size_t i = 0; i < 10; i++) {
        std::cout << (data.insert(std::make_pair(i, i)).second);
    }
}