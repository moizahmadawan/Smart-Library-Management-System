#include "Library.h"
#include "MergeSort.h"
#include <iostream>
#include <vector>
using namespace std;

bool Library::addBook(int id, const string &title, const string &author,
                      int year, bool record) {
    Book *b = new Book(id, title, author, year);
    if (!books.insert(b)) { delete b; return false; }   // duplicate ID
    titleIndex.insert(b);
    if (record) undoStack.push({ADD_BOOK, id, "", ""});
    return true;
}

bool Library::removeBook(int id) {
    Book *b = books.search(id);
    if (!b) return false;
    titleIndex.remove(b);   // BST first, it needs the book's title
    books.remove(id);       // then free the book from the hash table
    return true;
}

void Library::issueBook(int id, const string &student) {
    Book *b = books.search(id);
    if (!b) { cout << "  Book not found.\n"; return; }

    if (!b->issued) {
        b->issued = true;
        b->issuedTo = student;
        undoStack.push({ISSUE_BOOK, id, student, ""});
        cout << "  Issued \"" << b->title << "\" to " << student << ".\n";
    } else {
        b->waiting.enqueue(student);
        cout << "  Already issued to " << b->issuedTo << ". " << student
             << " added to waiting list (position " << b->waiting.size() << ").\n";
    }
}

void Library::returnBook(int id) {
    Book *b = books.search(id);
    if (!b) { cout << "  Book not found.\n"; return; }
    if (!b->issued) { cout << "  This book is not issued.\n"; return; }

    string prev = b->issuedTo, next = "";
    cout << "  " << prev << " returned \"" << b->title << "\".\n";

    if (!b->waiting.empty()) {
        next = b->waiting.dequeue();     // next student in queue gets it
        b->issuedTo = next;
        cout << "  Auto-issued to next in queue: " << next << ".\n";
    } else {
        b->issued = false;
        b->issuedTo = "";
    }
    undoStack.push({RETURN_BOOK, id, prev, next});
}

void Library::undo() {
    if (undoStack.empty()) { cout << "  Nothing to undo.\n"; return; }

    Action a = undoStack.pop();
    Book *b = books.search(a.bookId);

    switch (a.type) {
    case ADD_BOOK:
        if (b) {
            removeBook(a.bookId);
            cout << "  Undo: book " << a.bookId << " removed.\n";
        } else {
            cout << "  Undo skipped: that book no longer exists.\n";
        }
        break;
    case ISSUE_BOOK:
        if (b) {
            b->issued = false;
            b->issuedTo = "";
            cout << "  Undo: issue cancelled.\n";
        } else {
            cout << "  Undo skipped: that book no longer exists.\n";
        }
        break;
    case RETURN_BOOK:
        if (b) {
            if (!a.nextStudent.empty()) b->waiting.pushFront(a.nextStudent);
            b->issued = true;
            b->issuedTo = a.student;
            cout << "  Undo: return cancelled, book is with " << a.student << " again.\n";
        } else {
            cout << "  Undo skipped: that book no longer exists.\n";
        }
        break;
    }
}

void Library::searchById(int id) const {
    Book *b = books.search(id);
    if (b) printBook(b);
    else cout << "  Not found.\n";
}

void Library::searchByTitle(const string &title) const {
    Book *b = titleIndex.searchExact(title);
    if (b) printBook(b);
    else cout << "  Not found.\n";
}

void Library::listSortedByTitle() const { titleIndex.printSorted(); }

void Library::listSortedBy(int mode) const {
    vector<Book *> v;
    books.collect(v);
    if (v.empty()) { cout << "  (no books)\n"; return; }
    mergeSort(v, 0, (int)v.size() - 1, mode);
    for (Book *b : v) printBook(b);
}

void Library::showWaiting(int id) const {
    Book *b = books.search(id);
    if (!b) { cout << "  Book not found.\n"; return; }
    if (b->waiting.empty()) cout << "  Waiting list is empty.\n";
    else {
        cout << "  Waiting list for \"" << b->title << "\":\n";
        b->waiting.display();
    }
}
