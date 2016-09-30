//
// Created by Impy on 26.09.2016.
//

#ifndef LRU_CACHE_LRU_CACHE_H
#define LRU_CACHE_LRU_CACHE_

#include <iostream>
struct lru_cache
{
    typedef int key_type;
    typedef int mapped_type;
    // Вы можете определить эти тайпдефы по вашему усмотрению.
    typedef std::pair<key_type, mapped_type> value_type;
//private:
    struct node
    {
        key_type     key;
        mapped_type mapped;

        node*        left;
        node*        right;
        node*        parent;

        node*        next;
        node*        prev;
    };
    node* root;
    size_t size;
    size_t capacity;

    struct iterator {
        node* data;
        node* before();
        node* next();
        iterator(node* data);
        bool operator ==(iterator& a);
        bool operator !=(iterator& a);
        value_type operator*();
        iterator& operator++();
        iterator operator++(int);
        iterator& operator--();
        iterator operator--(int);
    };

    node* erase_without_delete(node*);

    void del(node*);
public:
    // Bidirectional iterator

    // Создает пустой lru_cache с указанной capacity.
    lru_cache(size_t capacity);

    // Деструктор. Вызывается при удалении объектов lru_cache.
    // Инвалидирует все итераторы ссылающиеся на элементы этого lru_cache
    // (включая итераторы ссылающиеся на элементы следующие за последними).
    ~lru_cache();

    // Поиск элемента.
    // Возвращает итератор на элемент найденный элемент, либо end().
    // Если элемент найден, он помечается как наиболее поздно использованный.
    iterator find(key_type);

    // Вставка элемента.
    // 1. Если такой ключ уже присутствует, вставка не производиться, возвращается итератор
    //    на уже присутствующий элемент и false.
    // 2. Если такого ключа ещё нет, производиться вставка, возвращается итератор на созданный
    //    элемент и true.
    // Если после вставки число элементов кеша превышает capacity, самый давно не
    // использованный элемент удаляется. Все итераторы на него инвалидируется.
    // Вставленный либо найденный с помощью этой функции элемент помечается как наиболее поздно
    // использованный.
    std::pair<iterator, bool> insert(value_type);

    // Удаление элемента.
    // Все итераторы на указанный элемент инвалидируются.
    void erase(iterator);

    // Возващает итератор на элемент с минимальный ключом.
    iterator begin() const;
    // Возващает итератор на элемент следующий за элементом с максимальным ключом.
    iterator end() const;
};
#endif //LRU_CACHE_LRU_CACHE_H
