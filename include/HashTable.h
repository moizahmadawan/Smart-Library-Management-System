#ifndef HASHTABLE_H
#define HASHTABLE_H

#include <vector>
#include "Book.h"

// ------------------------------------------------------------
// Hash Table with separate chaining.
// Key = book ID. Hash function = id % SIZE.
// insert / search / remove : O(1) average
// ------------------------------------------------------------
class HashTable {
    static const int SIZE = 101;   // prime number reduces collisions
    Book *table[SIZE];

    int hashFn(int id) const { return id % SIZE; }

public:
    HashTable() { for (int i = 0; i < SIZE; i++) table[i] = nullptr; }

    ~HashTable() {
        for (int i = 0; i < SIZE; i++) {
            Book *p = table[i];
            while (p) { Book *t = p; p = p->next; delete t; }
        }
    }

    HashTable(const HashTable &) = delete;
    HashTable &operator=(const HashTable &) = delete;

    bool insert(Book *b) {
        if (search(b->id)) return false;   // duplicate ID
        int h = hashFn(b->id);
        b->next = table[h];                // insert at head of chain
        table[h] = b;
        return true;
    }

    Book *search(int id) const {
        for (Book *p = table[hashFn(id)]; p; p = p->next)
            if (p->id == id) return p;
        return nullptr;
    }

    bool remove(int id) {
        int h = hashFn(id);
        Book *prev = nullptr;
        for (Book *p = table[h]; p; prev = p, p = p->next) {
            if (p->id == id) {
                if (prev) prev->next = p->next;
                else table[h] = p->next;
                delete p;
                return true;
            }
        }
        return false;
    }

    // Collect all books into a vector (used for sorting)
    void collect(std::vector<Book *> &out) const {
        for (int i = 0; i < SIZE; i++)
            for (Book *p = table[i]; p; p = p->next) out.push_back(p);
    }
};

#endif
