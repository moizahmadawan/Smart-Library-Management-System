#ifndef BST_H
#define BST_H

#include <iostream>
#include <string>
#include "Book.h"
#include "Utils.h"

// ------------------------------------------------------------
// Binary Search Tree, ordered by lowercase title.
// insert / search / remove : O(log n) average, O(n) worst case
// In-order traversal prints books in alphabetical order.
// ------------------------------------------------------------
struct TNode {
    std::string key;
    Book *book;
    TNode *l, *r;
};

class BST {
    TNode *root;

    TNode *insertNode(TNode *r, const std::string &key, Book *b) {
        if (!r) return new TNode{key, b, nullptr, nullptr};
        if (key < r->key) r->l = insertNode(r->l, key, b);
        else r->r = insertNode(r->r, key, b);   // equal titles go right
        return r;
    }

    TNode *removeNode(TNode *r, const std::string &key, int id) {
        if (!r) return nullptr;
        if (key < r->key) r->l = removeNode(r->l, key, id);
        else if (key > r->key) r->r = removeNode(r->r, key, id);
        else if (r->book->id != id) r->r = removeNode(r->r, key, id); // same title, other book
        else {
            if (!r->l) { TNode *t = r->r; delete r; return t; }  // 0 or 1 child
            if (!r->r) { TNode *t = r->l; delete r; return t; }
            // 2 children: replace with in-order successor
            TNode *m = r->r;
            while (m->l) m = m->l;
            std::string k = m->key;
            Book *mb = m->book;
            r->key = k;
            r->book = mb;
            r->r = removeNode(r->r, k, mb->id);
        }
        return r;
    }

    void inorder(TNode *r) const {
        if (!r) return;
        inorder(r->l);
        printBook(r->book);
        inorder(r->r);
    }

    void destroy(TNode *r) {
        if (!r) return;
        destroy(r->l);
        destroy(r->r);
        delete r;
    }

public:
    BST() : root(nullptr) {}
    ~BST() { destroy(root); }

    BST(const BST &) = delete;
    BST &operator=(const BST &) = delete;

    void insert(Book *b) { root = insertNode(root, toLower(b->title), b); }
    void remove(Book *b) { root = removeNode(root, toLower(b->title), b->id); }

    void printSorted() const {
        if (!root) { std::cout << "  (no books)\n"; return; }
        inorder(root);
    }

    Book *searchExact(const std::string &title) const {
        std::string key = toLower(title);
        TNode *p = root;
        while (p) {
            if (key == p->key) return p->book;
            p = (key < p->key) ? p->l : p->r;
        }
        return nullptr;
    }
};

#endif
