#ifndef BOOK_H
#define BOOK_H

#include <iostream>
#include <string>
#include "Queue.h"

struct Book {
    int id;
    std::string title, author;
    int year;
    bool issued;
    std::string issuedTo;
    Queue waiting;   // students waiting for this book
    Book *next;      // used for hash table chaining

    Book(int i, std::string t, std::string a, int y)
        : id(i), title(t), author(a), year(y),
          issued(false), next(nullptr) {}
};

inline void printBook(const Book *b) {
    std::cout << "  [ID " << b->id << "] " << b->title << " | "
              << b->author << " | " << b->year << " | ";
    if (b->issued) std::cout << "ISSUED to " << b->issuedTo;
    else std::cout << "Available";
    if (!b->waiting.empty()) std::cout << " | Waiting: " << b->waiting.size();
    std::cout << "\n";
}

#endif
