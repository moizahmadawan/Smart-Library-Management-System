#ifndef LIBRARY_H
#define LIBRARY_H

#include <string>
#include "HashTable.h"
#include "BST.h"
#include "Stack.h"

// Ties all data structures together:
//   HashTable -> search by ID     BST   -> search/list by title
//   Queue     -> waiting list     Stack -> undo
//   MergeSort -> sorted listings
class Library {
    HashTable books;
    BST titleIndex;
    Stack undoStack;

public:
    bool addBook(int id, const std::string &title, const std::string &author,
                 int year, bool record = true);
    bool removeBook(int id);

    void issueBook(int id, const std::string &student);
    void returnBook(int id);
    void undo();

    void searchById(int id) const;
    void searchByTitle(const std::string &title) const;
    void listSortedByTitle() const;
    void listSortedBy(int mode) const;   // 1 = year, 2 = author, 3 = id
    void showWaiting(int id) const;
};

#endif
